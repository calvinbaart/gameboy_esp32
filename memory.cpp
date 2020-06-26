#include "memory.h"
#include "video.h"
#include "gameboy_cpu.h"

Memory::Memory(GameboyCPU *cpu) : bios_enabled(true), vram_bank()
{
    this->cpu = cpu;

    vram_bank = 0;
    wram_bank = 1;

    memset(video_ram, 0xFF, 2 * 0x2000);
    memset(hram, 0xFF, 127);
    memset(oam_ram, 0xFF, 0x0A);
    memset(ram, 0xFF, 0x8000);
    memset(wram, 0xFF, 8 * 0x1000);
}

void Memory::set_bios(File bios_file)
{
    bios_length = bios_file.size();
    bios = new uint8_t[bios_length];
    bios_file.read(bios, bios_length);
}

void Memory::set_rom(File rom)
{
}

void Memory::write_video_ram(long position, long bank, uint8_t data)
{
    if (!bios_enabled) {
        video_ram[0][position - 0x8000] = data & 0xFF;
        return;
    }

    video_ram[bank][position - 0x8000] = data & 0xFF;
}

uint8_t Memory::read_video_ram(long position, long bank)
{
    if (!bios_enabled) {
        return video_ram[0][position - 0x8000];
    }

    return video_ram[bank][position - 0x8000];
}

long Memory::read8(long position)
{
    if (bios != nullptr && bios_enabled)
    {
        if (position < bios_length && (position < 0x100 || position >= 0x200))
        {
            return bios[position];
        }
    }

    if (read_registers.find(position) != read_registers.end() && read_registers[position] != nullptr)
    {
        return read_registers[position](position);
    }

    switch (position & 0xF000)
    {
        case 0x8000:
        case 0x9000:
            return read_video_ram(position, vram_bank);
            
        case 0xC000:
            return read_work_ram(position, 1);
            
        case 0xD000:
            return read_work_ram(position, wram_bank);
            
        case 0xF000:
            if (position >= 0xFF80 && position <= 0xFFFE)
            {
                return hram[position - 0xFF80];
            }
            else if (position >= 0xFE00 && position <= 0xFE9F)
            {
                return oam_ram[position - 0xFE00];
            }
    
        default:
//            if (this._controller)
//            {
//                return this._controller.read(position);
//            }
//            else
//            {
                return read_internal(position);
//            }
    }

    return 0xFF;
}

void Memory::write8(long position, long data)
{
    if (bios != nullptr && bios_enabled) {
        if (position < bios_length && (position < 0x100 || position >= 0x200)) {
            bios[position] = data & 0xFF;
            return;
        }
    }

    if (write_registers.find(position) != write_registers.end() && write_registers[position] != nullptr)
    {
        write_registers[position](position, data);
    }

    switch (position & 0xF000) {
        case 0x8000:
        case 0x9000:
            write_video_ram(position, vram_bank, data);
            break;

        case 0xC000:
        case 0xD000:
            write_work_ram(position, wram_bank, data);
            break;

        case 0xF000:
            if (position >= 0xFF80 && position <= 0xFFFE) {
                hram[position - 0xFF80] = data & 0xFF;
                break;
            } else if (position >= 0xFE00 && position <= 0xFE9F) {
                oam_ram[position - 0xFE00] = data & 0xFF;
                cpu->get_video()->oam_write(position - 0xFE00, data & 0xFF);
                break;
            }

        default:
//            if (this._controller) {
//                this._controller.write(position, data & 0xFF);
//            } else {
                  write_internal(position, data & 0xFF);
//            }
    }
}

void Memory::add_register(long location, long (*callback_read)(long), void (*callback_write)(long, long))
{
    read_registers[location] = callback_read;
    write_registers[location] = callback_write;
}

uint8_t Memory::read_work_ram(long position, long bank)
{
    switch (position & 0xF000)
    {
        default:
        case 0xC000:
            return wram[0][position - 0xC000];
        
        case 0xD000:
            return wram[1][position - 0xD000];
    }
}

uint8_t Memory::read_internal(long position)
{
    return 0xFF;
//    if (!this._rom || position >= this._rom.length) {
//        return 0xFF;
//    }
//
//    return this._rom[position];
}

void Memory::write_work_ram(long position, long bank, uint8_t data)
{
    switch (position & 0xF000)
    {
        default:
        case 0xC000:
            wram[0][position - 0xC000] = data & 0xFF;
            break;

        case 0xD000:
            wram[1][position - 0xD000] = data & 0xFF;
            break;
    }
}

void Memory::write_internal(long position, uint8_t data)
{
//    if (!this._rom) {
//        return;
//    }
//
//    this._rom[position] = data & 0xFF;
}
