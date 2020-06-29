#ifndef _MEMORY_H_
#define _MEMORY_H_

#include "board_config.h"
#include "memory_controller.h"

class GameboyCPU;
class Memory
{
private:
    GameboyCPU* cpu;

    uint8_t* bios;
    long bios_length;
    bool bios_enabled;

    uint8_t* rom;

    uint8_t** video_ram;
    uint8_t* hram;
    uint8_t** wram;
    uint8_t* oam_ram;
    uint8_t* ram;

    long vram_bank;
    long wram_bank;

    IMemoryController* controller;

    void create_controller(long type);

    bool write_register(long position, long data);
    long read_register(long position);
public:
    Memory(GameboyCPU* cpu);

    void set_bios(File bios);
    bool set_rom(File rom);

    void disable_bios();

    long read8(long location);
    void write8(long location, long byte);

    long read_ram8(long location);
    void write_ram8(long location, long byte);

    long read_video_ram(long position, long bank);
    void write_video_ram(long position, long bank, long data);

    long read_work_ram(long position, long bank);
    long read_internal(long position);
    
    void write_work_ram(long position, long bank, long data);
    void write_internal(long position, long data);

    void perform_oam_dma_transfer(long position);
};

#endif
