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
    HL
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
class GameboyCPU
{
private:
    Registers registers;
    Memory* memory;
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

    RegisterType read_register_type(long val, bool useAF);
    RegisterType read_byte_register_type(long val);

    bool step();

    long get_cycles();

    long set(RegisterType register, long val);
};

#endif
