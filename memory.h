#ifndef _MEMORY_H_
#define _MEMORY_H_

#include "board_config.h"

class GameboyCPU;
class Memory
{
private:
    GameboyCPU* cpu;

    uint8_t* bios;
    long bios_length;
    bool bios_enabled;

    uint8_t video_ram[2][0x2000];

    long vram_bank;

    void write_video_ram(long position, long bank, long data);
public:
    Memory(GameboyCPU* cpu);

    void set_bios(File bios);
    void set_rom(File rom);

    long read8(long location);
    void write8(long location, long byte);
};

#endif
