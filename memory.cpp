#include "memory.h"
#include "video.h"
#include "mbc1.h"
#include "mbc3.h"
#include "gameboy_cpu.h"

static long read_register_invalid(long position)
{
    return 0xFF;
}

static void write_register(long position, long data)
{
    GameboyCPU::instance->get_memory()->disable_bios();
}

Memory::Memory(GameboyCPU *cpu) : bios_enabled(true), vram_bank()
{
    this->cpu = cpu;

    controller = nullptr;
    rom = nullptr;

    vram_bank = 0;
    wram_bank = 1;

    memset(video_ram, 0xFF, 2 * 0x2000);
    memset(hram, 0xFF, 127);
    memset(oam_ram, 0xFF, 0x0A);
    memset(ram, 0xFF, 0x8000);
    memset(wram, 0xFF, 2 * 0x1000);

    add_register(0xFF50, &::read_register_invalid, &::write_register);
}

void Memory::set_bios(File bios_file)
{
    bios_length = bios_file.size();
    bios = new uint8_t[bios_length];
    bios_file.read(bios, bios_length);
}

void Memory::set_rom(File rom_file)
{
    rom_length = rom_file.size();
    rom = new uint8_t[rom_length];
    rom_file.read(rom, rom_length);

    long rom_type = rom[0x147];
    create_controller(rom_type);
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
            if (controller != nullptr)
            {
                return controller->read(position);
            }
            else
            {
                return read_internal(position);
            }
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
            if (controller != nullptr) {
                controller->write(position, data & 0xFF);
            } else {
                write_internal(position, data & 0xFF);
            }
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
    if (rom == nullptr || position >= rom_length) {
        return 0xFF;
    }

    return rom[position];
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
    if (rom == nullptr) {
        return;
    }

    rom[position] = data & 0xFF;
}

void Memory::perform_oam_dma_transfer(long position)
{
    for (long i = 0; i <= 0x9F; i++)
    {
        oam_ram[i] = read8(position + i);
        cpu->get_video()->oam_write(i, oam_ram[i]);
    }
}

void Memory::disable_bios()
{
    bios_enabled = false;
}

long Memory::read_ram8(long location)
{
    return ram[location];
}

void Memory::write_ram8(long location, long byte)
{
    ram[location] = byte & 0xFF;
}

void Memory::create_controller(long type)
{
    switch ((RomType)type)
    {
        case RomType::MBC1:
        case RomType::MBC1RAM:
        case RomType::MBC1RAMBATTERY:
            controller = new MBC1(this);
            break;
        
        case RomType::MBC3:
        case RomType::MBC3RAM:
        case RomType::MBC3RAMBATTERY:
        case RomType::MBC3TIMERBATTERY:
        case RomType::MBC3TIMERRAMBATTERY:
            controller = new MBC3(this);
            break;
        
        // case RomType::MBC5:
        // case RomType::MBC5RAM:
        // case RomType::MBC5RAMBATTERY:
        // case RomType::MBC5RUMBLE:
        // case RomType::MBC5RUMBLERAM:
        // case RomType::MBC5RUMBLERAMBATTERY:
        //     this._controller = new MBC5(this);
        //     break;
        
        case RomType::UNKNOWN:
        case RomType::ROMONLY:
            // this._controller = new RomOnlyMemoryController(this);
            break;
        
        default:
            Serial.println("UNKNOWN ROM TYPE: " + String(type));
            // this._controller = new RomOnlyMemoryController(this);
            break;
    }
}
