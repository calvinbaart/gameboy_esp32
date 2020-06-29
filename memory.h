#ifndef _MEMORY_H_
#define _MEMORY_H_

#include "board_config.h"
#include "memory_controller.h"

class GameboyCPU;
class Memory
{
private:
    GameboyCPU* cpu;
    File rom_file;

    uint8_t* bios;
    long bios_length;
    bool bios_enabled;

    uint8_t* current_block;
    long current_block_index;
    bool current_block_changed;
    long rom_length;

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

    uint8_t read_byte(long location);
    void write_byte(long location, uint8_t data);
    long switch_block(long location);
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
};

#endif
