#include "memory.h"
#include "video.h"
#include "mbc1.h"
#include "mbc3.h"
#include "gameboy_cpu.h"
#include "timer.h"

Memory::Memory(GameboyCPU *cpu) : bios_enabled(true), vram_bank()
{
    this->cpu = cpu;

    controller = nullptr;
    rom = nullptr;

    vram_bank = 0;
    wram_bank = 1;

    video_ram = new uint8_t*[2];
    video_ram[0] = new uint8_t[0x2000];
    video_ram[1] = new uint8_t[0x2000];

    hram = new uint8_t[127];

    wram = new uint8_t*[2];
    wram[0] = new uint8_t[0x1000];
    wram[1] = new uint8_t[0x1000];

    oam_ram = new uint8_t[0xA0];
    ram = new uint8_t[0x8000];

    memset(video_ram[0], 0xFF, 0x2000);
    memset(video_ram[1], 0xFF, 0x2000);
    memset(hram, 0xFF, 127);
    memset(wram[0], 0xFF, 0x1000);
    memset(wram[1], 0xFF, 0x1000);
    memset(oam_ram, 0xFF, 0x0A);
    memset(ram, 0xFF, 0x8000);
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

    if (position >= 0xFF00 && position <= 0xFF7F)
    {
        return read_register(position);
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

    if (position >= 0xFF00 && position <= 0xFF7F)
    {
        write_register(position, data);
        return;
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
            Serial.println("Using MBC1");
            controller = new MBC1(this);
            break;
        
        case RomType::MBC3:
        case RomType::MBC3RAM:
        case RomType::MBC3RAMBATTERY:
        case RomType::MBC3TIMERBATTERY:
        case RomType::MBC3TIMERRAMBATTERY:
            Serial.println("Using MBC3");
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
            Serial.println("Using ROMONLY");
            break;
        
        default:
            Serial.println("UNKNOWN ROM TYPE: " + String(type));
            break;
    }
}

void Memory::write_register(long position, long data)
{
    switch (position)
    {
        case 0xFF00: // P1
            // cant write to P1
            break;

        case 0xFF01: // SB
            GameboyCPU::instance->special_register_write(SpecialRegisterType::SB, data);
            break;

        case 0xFF02: // SC
            GameboyCPU::instance->special_register_write(SpecialRegisterType::SC, data);
            break;

        case 0xFF0F: // IF
            GameboyCPU::instance->special_register_write(SpecialRegisterType::IF, data);
            break;

        case 0xFFFF: // IE
            GameboyCPU::instance->special_register_write(SpecialRegisterType::IE, data);
            break;

        case 0xFF07: // Timer TAC
            Timer::instance->tac = data & 0xFF;
            break;

        case 0xFF04: // Timer DIV
            Timer::instance->div = 0;
            break;

        case 0xFF05: // Timer TIMA
            Timer::instance->tima = data & 0xFF;
            break;

        case 0xFF06: // Timer TMA
            Timer::instance->tma = data & 0xFF;
            break;

        case 0xFF50: // bios disable
            GameboyCPU::instance->get_memory()->disable_bios();
            GameboyCPU::instance->bootstrap_completed = true;
            break;

        case 0xFF40: //LCDC
            Video::instance->write_register(VideoRegisterType::LCDC, data);
            return;

        case 0xFF41: //STAT
            Video::instance->write_register(VideoRegisterType::STAT, data);
            return;

        case 0xFF42: //SCY
            Video::instance->write_register(VideoRegisterType::SCY, data);
            return;

        case 0xFF43: //SCX
            Video::instance->write_register(VideoRegisterType::SCX, data);
            return;

        case 0xFF44: //LY
            Video::instance->write_register(VideoRegisterType::LY, data);
            return;

        case 0xFF45: //LYC
            Video::instance->write_register(VideoRegisterType::LYC, data);
            return;

        case 0xFF46: //DMA
            Video::instance->write_register(VideoRegisterType::DMA, data);
            return;

        case 0xFF47: //BGP
            Video::instance->write_register(VideoRegisterType::BGP, data);
            return;

        case 0xFF48: //OBP0
            Video::instance->write_register(VideoRegisterType::OBP0, data);
            return;

        case 0xFF49: //OBP1
            Video::instance->write_register(VideoRegisterType::OBP1, data);
            return;

        case 0xFF4A: //WY
            Video::instance->write_register(VideoRegisterType::WY, data);
            return;

        case 0xFF4B: //WX
            Video::instance->write_register(VideoRegisterType::WX, data);
            return;

        // default:
        //     Serial.println("unknown write register: " + String(position));
    }
}

long Memory::read_register(long position)
{
    switch (position)
    {
        case 0xFF00: // P1
            return GameboyCPU::instance->special_register_read(SpecialRegisterType::P1);

        case 0xFF01: // SB
            return GameboyCPU::instance->special_register_read(SpecialRegisterType::SB);

        case 0xFF02: // SC
            return GameboyCPU::instance->special_register_read(SpecialRegisterType::SC);

        case 0xFF0F: // IF
            return GameboyCPU::instance->special_register_read(SpecialRegisterType::IF);

        case 0xFFFF: // IE
            return GameboyCPU::instance->special_register_read(SpecialRegisterType::IE);

        case 0xFF07: // Timer TAC
            return Timer::instance->tac | 0b11111000;

        case 0xFF04: // Timer DIV
            return Timer::instance->div;

        case 0xFF05: // Timer TIMA
            return Timer::instance->tima;

        case 0xFF06: // Timer TMA
            return Timer::instance->tma;

        case 0xFF50: // bios disable
            return 0xFF;

        case 0xFF40: //LCDC
            return Video::instance->read_register(VideoRegisterType::LCDC);

        case 0xFF41: //STAT
            return Video::instance->read_register(VideoRegisterType::STAT);

        case 0xFF42: //SCY
            return Video::instance->read_register(VideoRegisterType::SCY);

        case 0xFF43: //SCX
            return Video::instance->read_register(VideoRegisterType::SCX);

        case 0xFF44: //LY
            return Video::instance->read_register(VideoRegisterType::LY);

        case 0xFF45: //LYC
            return Video::instance->read_register(VideoRegisterType::LYC);

        case 0xFF46: //DMA
            return Video::instance->read_register(VideoRegisterType::DMA);

        case 0xFF47: //BGP
            return Video::instance->read_register(VideoRegisterType::BGP);

        case 0xFF48: //OBP0
            return Video::instance->read_register(VideoRegisterType::OBP0);

        case 0xFF49: //OBP1
            return Video::instance->read_register(VideoRegisterType::OBP1);

        case 0xFF4A: //WY
            return Video::instance->read_register(VideoRegisterType::WY);

        case 0xFF4B: //WX
            return Video::instance->read_register(VideoRegisterType::WX);

        // default:
        //     Serial.println("unknown read register: " + String(position));
    }

    return 0xFF;
}