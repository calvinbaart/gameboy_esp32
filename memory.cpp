#include "memory.h"
#include "gameboy_cpu.h"

Memory::Memory(GameboyCPU *cpu) : bios_enabled(true), vram_bank()
{
    this->cpu = cpu;

    memset(video_ram, 2 * 0x2000, 0xFF);
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

void Memory::write_video_ram(long position, long bank, long data)
{
    if (!bios_enabled) {
        video_ram[0][position - 0x8000] = data & 0xFF;
        return;
    }

    video_ram[bank][position - 0x8000] = data & 0xFF;
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

    Serial.println("TODO: finish read8");

    // if (this._registers[position] != undefined)
    // {
    //     return this._registers[position].read();
    // }

    // switch (position & 0xF000)
    // {
    //     case 0x8000:
    //     case 0x9000:
    //         return this.readVideoRam(position, this._vramBank);

    //     case 0xC000:
    //         return this.readWorkRam(position, 1);

    //     case 0xD000:
    //         return this.readWorkRam(position, this._wramBank);

    //     case 0xF000:
    //         if (position >= 0xFF80 && position <= 0xFFFE)
    //         {
    //             return this._hram[position - 0xFF80];
    //         }
    //         else if (position >= 0xFE00 && position <= 0xFE9F)
    //         {
    //             return this._oamram[position - 0xFE00];
    //         }

    //     default:
    //         if (this._controller)
    //         {
    //             return this._controller.read(position);
    //         }
    //         else
    //         {
    //             return this.readInternal8(position);
    //         }
    // }

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

// todo: check registers
//    if (this._registers[position] !== undefined) {
//        this._registers[position].write(data);
//        return;
//    }

    switch (position & 0xF000) {
        case 0x8000:
        case 0x9000:
            write_video_ram(position, vram_bank, data);
            break;

        case 0xC000:
        case 0xD000:
              Serial.println("TODO: implement write work ram");
//            this.writeWorkRam(position, this._wramBank, data);
            break;

        case 0xF000:
              Serial.println("TODO: implement write h ram / oam ram");
//            if (position >= 0xFF80 && position <= 0xFFFE) {
//                this._hram[position - 0xFF80] = data & 0xFF;
//                break;
//            } else if (position >= 0xFE00 && position <= 0xFE9F) {
//                this._oamram[position - 0xFE00] = data & 0xFF;
//                this._cpu.Display.oamWrite(position - 0xFE00, data & 0xFF);
//                break;
//            }
            break;

        default:
              Serial.println("TODO: implement write rom");
//            if (this._controller) {
//                this._controller.write(position, data & 0xFF);
//            } else {
//                  write_internal8(position, data & 0xFF);
//            }
    }
}
