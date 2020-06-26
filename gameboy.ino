#include "board_config.h"
#include "gameboy_cpu.h"

GxIO_Class io(SPI, /*CS=5*/ ELINK_SS, /*DC=*/ELINK_DC, /*RST=*/ELINK_RESET);
GxEPD_Class display(io, /*RST=*/ELINK_RESET, /*BUSY=*/ELINK_BUSY);

long previousTime;
bool stopEmulation;

GameboyCPU cpu(&display);

void setup()
{
    Serial.begin(115200);

    SPI.begin(SPI_CLK, SPI_MISO, SPI_MOSI, ELINK_SS);
    display.init();

    display.setRotation(1);
    display.fillScreen(GxEPD_WHITE);
    display.setTextColor(GxEPD_BLACK);
    display.setFont(&FreeMonoBold9pt7b);
    display.setCursor(0, 16);

    SPIClass sdSPI(VSPI);
    sdSPI.begin(SDCARD_CLK, SDCARD_MISO, SDCARD_MOSI, SDCARD_SS);

    if (!SD.begin(SDCARD_SS, sdSPI))
    {
        display.println("SDCARD MOUNT FAILED");
    }
    else
    {
        display.println("SDCARD MOUNTED");

        uint32_t cardSize = SD.cardSize() / (1024 * 1024);

        display.println("SDCARD SIZE: " + String(cardSize) + "MB");

        File dmgBoot = SD.open("/dmg_boot.bin");
        cpu.set_bios(dmgBoot);
        dmgBoot.close();

        SD.end();
    }

    display.updateWindow(0, 0, display.width(), display.height());
}

void printDirectory(File dir, int numTabs)
{
    while (true)
    {
        File entry = dir.openNextFile();
        if (!entry)
        {
            // no more files
            break;
        }

        String str = "";
        for (uint8_t i = 0; i < numTabs; i++)
        {
            str += " ";
        }

        str += entry.name();

        if (entry.isDirectory())
        {
            str += "/";
            display.println(str);
            printDirectory(entry, numTabs + 1);
        }
        else
        {
            // files have sizes, directories do not
            str += "  ";
            str += entry.size();

            display.println(str);
        }

        entry.close();
    }
}

void loop()
{
    long now = millis();
    long delta = now - previousTime;
    previousTime = now;

    long cycles = floor(((4194304 * 2.4f) / 1000.0) * delta);

    if (cycles >= (floor(4194304 / 60.0f) * 2.4f))
    {
        cycles = floor(4194304 / 60.0f) * 2.4f;
    }

    if (stopEmulation)
    {
        return;
    }

    long startCycles = cpu.get_cycles();
    while ((cpu.get_cycles() - startCycles) < cycles)
    {
        if (!cpu.step())
        {
            stopEmulation = true;
            break;
        }
    }

    // todo: gpu update
}
