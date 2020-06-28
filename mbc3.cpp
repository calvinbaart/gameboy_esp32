#include "mbc3.h"
#include "memory.h"

MBC3::MBC3(Memory* memory)
{
    start_millis = millis();
    this->memory = memory;

    rom_bank_number = 1;
    ram_bank_number = 1;
    clock_register = 0;

    ram_enabled = false;

    hour = 0;
    second = 0;
    minute = 0;
    day_lower = 0;
    day_upper = 0;

    second = (second + 40) % 0x3C;
    minute = (minute + 40) % 0x3C;
    hour = (hour + 12) % 0x18;

    day_lower = 0;
    day_upper &= ~0x1;
    day_upper &= ~(1 << 7);

    latch_clock();

    latch_clock_data = -1;
}

void MBC3::latch_clock()
{
    long delta_millis = millis() - start_millis;

    day_lower = 0;
    day_upper &= ~0x1;
    day_upper &= ~(1 << 7);

    if (delta_millis == 0)
    {
        return;
    }

    hour = floor(delta_millis / 3600000.0f);
    
    delta_millis -= hour * 3600000.0f;

    if (delta_millis == 0)
    {
        return;
    }

    minute = floor(delta_millis / 60000.0f);

    delta_millis -= minute * 60000.0f;

    if (delta_millis == 0)
    {
        return;
    }

    second = floor(delta_millis / 1000.0f);

    second = (second + 40) % 0x3C;
    minute = (minute + 40) % 0x3C;
    hour = (hour + 12) % 0x18;
}

long MBC3::read(long position)
{
    switch (position & 0xF000)
    {
        case 0x4000:
        case 0x5000:
        case 0x6000:
        case 0x7000:
            position += (rom_bank_number - 1) * 0x4000;

            return memory->read_internal(position);

        case 0xA000:
        case 0xB000:
            if (ram_enabled && clock_register == 0) {
                return memory->read_ram8((position - 0xA000) + (ram_bank_number * 0x2000));
            } else if (clock_register != 0) {
                switch ((TimeKey)clock_register)
                {
                    case TimeKey::DayLower:
                        return day_lower;

                    case TimeKey::DayUpper:
                        return day_upper;

                    case TimeKey::Hour:
                        return hour;

                    case TimeKey::Minute:
                        return minute;

                    case TimeKey::Second:
                        return second;
                }
            }

            return 0xFF;

        default:
            return memory->read_internal(position);
    }
}

void MBC3::write(long position, long value)
{
    switch (position & 0xF000)
    {
        case 0x0000:
        case 0x1000:
            if (ram_enabled && (value & 0x0F) != 0x0A) {
                // memory->saveRam();
            } else if (!ram_enabled && (value & 0x0F) == 0x0A) {
                // memory->loadRam();
            }

            ram_enabled = (value & 0x0F) == 0x0A;
            return;

        case 0x2000:
        case 0x3000:
            rom_bank_number = value;
            return;

        case 0x4000:
        case 0x5000:
            if (value <= 0x03) {
                ram_bank_number = value & 0x03;
                clock_register = 0;
            } else {
                clock_register = value;
            }
            return;

        case 0x6000:
        case 0x7000:
            if (value == 1 && latch_clock_data == 0) {
                latch_clock();
            }

            latch_clock_data = value;
            return;

        case 0xA000:
        case 0xB000:
            if (ram_enabled && clock_register == 0) {
                memory->write_ram8((position - 0xA000) + (ram_bank_number * 0x2000), value);
            } else if (clock_register != 0) {
                switch ((TimeKey)clock_register)
                {
                    case TimeKey::DayLower:
                        day_lower = value;
                        break;

                    case TimeKey::DayUpper:
                        day_upper = value;
                        break;

                    case TimeKey::Hour:
                        hour = value;
                        break;

                    case TimeKey::Minute:
                        minute = value;
                        break;

                    case TimeKey::Second:
                        second = value;
                        break;
                }
            }
            return;

        default:
            memory->write_internal(position, value);
    }
}
