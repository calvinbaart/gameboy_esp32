#ifndef _MEMORY_H_
#define _MEMORY_H_

#include "board_config.h"
#include "memory_controller.h"
#include <map>

class GameboyCPU;
class Memory
{
private:
    GameboyCPU* cpu;

    uint8_t* bios;
    long bios_length;
    bool bios_enabled;

    uint8_t* rom;
    long rom_length;

    uint8_t video_ram[2][0x2000];
    uint8_t hram[127];
    uint8_t wram[2][0x1000];
    uint8_t oam_ram[0xA0];
    uint8_t ram[0x8000];

    std::map<long, long (*)(long)> read_registers;
    std::map<long, void (*)(long, long)> write_registers;

    long vram_bank;
    long wram_bank;

    IMemoryController* controller;

    void create_controller(long type);
public:
    Memory(GameboyCPU* cpu);

    void set_bios(File bios);
    void set_rom(File rom);

    void disable_bios();

    long read8(long location);
    void write8(long location, long byte);

    long read_ram8(long location);
    void write_ram8(long location, long byte);

    uint8_t read_video_ram(long position, long bank);
    void write_video_ram(long position, long bank, uint8_t data);

    uint8_t read_work_ram(long position, long bank);
    uint8_t read_internal(long position);
    
    void write_work_ram(long position, long bank, uint8_t data);
    void write_internal(long position, uint8_t data);

    void perform_oam_dma_transfer(long position);

    void add_register(long location, long (*callback_read)(long), void (*callback_write)(long, long));
};

#endif
