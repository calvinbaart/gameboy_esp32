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
public:
    Memory(GameboyCPU* cpu);

    void set_bios(File bios);
    void set_rom(File rom);

    long read8(long location);
    void write8(long byte);
};

#endif
