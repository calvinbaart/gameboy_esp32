#ifndef _GAMEBOY_CPU_H_
#define _GAMEBOY_CPU_H_

#include "board_config.h"
#include "registers.h"

enum class RegisterType
{
    A,
    B,
    C,
    D,
    E,
    F,
    H,
    L,
    AF,
    SP,
    PC,
    BC,
    DE,
    HL,
    None
};

enum Flags {
    ZeroFlag = 0b10000000,
    AddSubFlag = 0b01000000,
    HalfCarryFlag = 0b00100000,
    CarryFlag = 0b00010000,
    Unused = 0b00001111
};

class GameboyCPU;
struct Instruction
{
    bool is_cb;
    long pc;
    long opcode;
    long ticks;

    GameboyCPU* cpu;

    void (*exec)(Instruction);
};

class Memory;
class Video;
class GameboyCPU
{
private:
    Registers registers;
    Memory* memory;
    Video* video;
    GxEPD_Class* display;
    long cycles;

    void tick(long num_cycles);
    Instruction fetch_and_decode();
public:
    GameboyCPU(GxEPD_Class* display);

    void set_bios(File bios);
    void set_rom(File rom);

    long read_u8();
    long read_u16();

    long read_s8();
    long read_s16();

    long increment(RegisterType reg, long num = 1);
    long decrement(RegisterType reg, long num = 1);

    Memory* get_memory();
    Video* get_video();

    RegisterType read_register_type(long val, bool useAF);
    RegisterType read_byte_register_type(long val);

    bool step();

    long get_cycles();
    void cycle(long num);

    long set(RegisterType reg, long value);
    long get(RegisterType reg);

    void clear_flags();
    void enable_flag(Flags flag);
    void disable_flag(Flags flag);
    bool is_flag_set(Flags flag);

    void push_stack(long num);
    long pop_stack();

    static GameboyCPU* instance;
};

#endif
