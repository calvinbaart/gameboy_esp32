#include "mbc1.h"
#include "memory.h"

MBC1::MBC1(Memory* memory)
{
    this->memory = memory;

    rom_bank_number = 1;
    ram_bank_number = 1;

    ram_banking = false;
    ram_enabled = false;
}

long MBC1::read(long position)
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
            if (ram_enabled) {
                if (!ram_banking) {
                    return memory->read_ram8(position - 0xA000);
                } else {
                    return memory->read_ram8((position - 0xA000) + (ram_bank_number * 0x2000));
                }
            }
            return 0xFF;
        
        default:
            return memory->read_internal(position);
    }
}

void MBC1::write(long position, long value)
{
    switch (position & 0xF000)
    {
        case 0x0000:
        case 0x1000:
            if (ram_enabled && (value & 0x0F) != 0x0A) {
                // memory->save_ram();
            } else if (!ram_enabled && (value & 0x0F) == 0x0A) {
                // memory->load_ram();
            }
            
            ram_enabled = (value & 0x0F) == 0x0A;
            return;
        
        case 0x2000:
        case 0x3000:
            if (!ram_banking) {
                rom_bank_number = (rom_bank_number & 0xE0) | (value & 0x1F);
            } else {
                rom_bank_number = value & 0x1F;
            }

            if (rom_bank_number == 0x00 || rom_bank_number == 0x20 || rom_bank_number == 0x40 || rom_bank_number == 0x60) {
                rom_bank_number++;
            }
            return;
        
        case 0x4000:
        case 0x5000:
            if (ram_banking) {
                ram_bank_number = value & 0x03;
            } else {
                rom_bank_number = (rom_bank_number & 0xCF) | (value << 4);

                if (rom_bank_number == 0x00 || rom_bank_number == 0x20 || rom_bank_number == 0x40 || rom_bank_number == 0x60) {
                    rom_bank_number++;
                }
            }
            return;
        
        case 0x6000:
        case 0x7000:
            ram_banking = value == 0x01;
            return;
        
        case 0xA000:
        case 0xB000:
            if (ram_enabled) {
                if (!ram_banking) {
                    memory->write_ram8(position - 0xA000, value);
                } else {
                    memory->write_ram8((position - 0xA000) + (ram_bank_number * 0x2000), value);
                }
            }
            return;
        
        default:
            memory->write_internal(position, value);
    }
}