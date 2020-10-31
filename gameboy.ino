#include "board_config.h"
#include "gameboy_cpu.h"

GxIO_Class io(SPI, /*CS=5*/ ELINK_SS, /*DC=*/ELINK_DC, /*RST=*/ELINK_RESET);
GxEPD_Class display(io, /*RST=*/ELINK_RESET, /*BUSY=*/ELINK_BUSY);

long previousTime;
bool stopEmulation;

GameboyCPU cpu(&display);
SPIClass sdSPI(VSPI);

long last_cycles = 0;
long last_time = 0;

const int a_pin = 32;
const int b_pin = 33;
const int start_pin = 25;
const int select_pin = 26;
const int up_pin = 27;
const int down_pin = 12;
const int left_pin = 13;
const int right_pin = 15;

void setup()
{
    pinMode(start_pin, INPUT);
    pinMode(select_pin, INPUT);
    pinMode(a_pin, INPUT);
    pinMode(b_pin, INPUT);
    pinMode(up_pin, INPUT);
    pinMode(down_pin, INPUT);
    // pinMode(left_pin, INPUT);
    pinMode(right_pin, INPUT);

    Serial.begin(115200);

    SPI.begin(SPI_CLK, SPI_MISO, SPI_MOSI, ELINK_SS);
    display.init();
    display.eraseDisplay();

    display.setRotation(1);
    display.fillScreen(GxEPD_WHITE);
    display.setTextColor(GxEPD_BLACK);
    display.setFont(&FreeMonoBold9pt7b);
    display.setCursor(0, 16);

    sdSPI.begin(SDCARD_CLK, SDCARD_MISO, SDCARD_MOSI, SDCARD_SS);

    if (!SD.begin(SDCARD_SS, sdSPI))
    {
        display.println("SDCARD MOUNT FAILED");
    }
    else
    {
        // display.println("SDCARD MOUNTED");

        uint32_t cardSize = SD.cardSize() / (1024 * 1024);

        // display.println("SDCARD SIZE: " + String(cardSize) + "MB");

        File dmgBoot = SD.open("/dmg_boot.bin");
        cpu.set_bios(dmgBoot);
        dmgBoot.close();

        File rom = SD.open("/pokemon.gb");
        cpu.set_rom(rom);
        rom.close();

        SD.end();
    }

    display.update();
}

bool color = false;

void loop()
{
    // long now = millis();

    cpu.key_state(Key::A, digitalRead(a_pin) == HIGH);
    cpu.key_state(Key::B, digitalRead(b_pin) == HIGH);
    cpu.key_state(Key::Start, digitalRead(start_pin) == HIGH);
    cpu.key_state(Key::Select, digitalRead(select_pin) == HIGH);
    cpu.key_state(Key::Up, digitalRead(up_pin) == HIGH);
    cpu.key_state(Key::Down, digitalRead(down_pin) == HIGH);
    // cpu.key_state(Key::Left, digitalRead(left_pin) == HIGH);
    // cpu.key_state(Key::Right, digitalRead(right_pin) == HIGH);

    // long delta = now - previousTime;

    // if (delta >= 5000) {
    //     color = !color;
    //     previousTime = now;
    // }

    // if (color) {
    //     display.fillRect(0, 0, display.width(), display.height(), GxEPD_BLACK);
    // } else {
    //     display.fillRect(0, 0, display.width(), display.height(), GxEPD_WHITE);
    // }

    // display.updateWindow(0, 0, display.width(), display.height());

    // if (delta == 0)
    // {
    //     return;
    // }

    // long cycles = floor(((4194304 * 2.4f) / 1000.0) * delta);

    // if (cycles >= (floor(4194304 / 60.0f) * 2.4f))
    // {
    //     cycles = floor(4194304 / 60.0f) * 2.4f;
    // }

    // if (stopEmulation)
    // {
    //     return;
    // }

    // long startCycles = cpu.get_cycles();
    // while (true)
    // {
        if (!cpu.step())
        {
            stopEmulation = true;
    //         break;
        }

    //     now = millis();

    //     if (now - last_time >= 1000) {
    //         long num_cycles = cpu.get_cycles() - last_cycles;

    //         Serial.printf("Cycles=%d\n", num_cycles);

    //         last_cycles = cpu.get_cycles();
    //         last_time = now;
    //     }
    // }
}
