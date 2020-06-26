#ifndef _MEMORY_H_
#define _MEMORY_H_

#include "board_config.h"
#include <map>

class GameboyCPU;
class Memory
{
private:
    GameboyCPU* cpu;

    uint8_t* bios;
    long bios_length;
    bool bios_enabled;

    uint8_t video_ram[2][0x2000];

    std::map<long, long (*)(long)> read_registers;
    std::map<long, void (*)(long, long)> write_registers;

    long vram_bank;
public:
    Memory(GameboyCPU* cpu);

    void set_bios(File bios);
    void set_rom(File rom);

    long read8(long location);
    void write8(long location, long byte);

    uint8_t read_video_ram(long position, long bank);
    void write_video_ram(long position, long bank, uint8_t data);

    void add_register(long location, long (*callback_read)(long), void (*callback_write)(long, long));
};

#endif
