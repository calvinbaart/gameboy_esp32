#include "memory.h"
#include "gameboy_cpu.h"

Memory::Memory(GameboyCPU *cpu) : bios_enabled(true)
{
    this->cpu = cpu;
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

void Memory::write8(long byte)
{
}
