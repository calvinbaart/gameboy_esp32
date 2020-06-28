#ifndef _GAMEBOY_CPU_H_
#define _GAMEBOY_CPU_H_

#include "board_config.h"
#include "registers.h"

enum RegisterType
{
    A = 1,
    B = 2,
    C = 3,
    D = 4,
    E = 5,
    F = 6,
    H = 7,
    L = 8,
    AF = 9,
    SP = 10,
    PC = 11,
    BC = 12,
    DE = 13,
    HL = 14,
    None = 15
};

enum class SpecialRegisterType
{
    P1,
    SB,
    SC,
    IF,
    IE
};

enum Interrupt
{
    VBlankInterrupt,
    LCDStatInterrupt,
    TimerInterrupt,
    SerialInterrupt,
    JoypadInterrupt
};

enum Flags {
    ZeroFlag = 0b10000000,
    AddSubFlag = 0b01000000,
    HalfCarryFlag = 0b00100000,
    CarryFlag = 0b00010000,
    Unused = 0b00001111
};

enum class RomType {
    UNKNOWN = -1,
    ROMONLY = 0x00,
    MBC1 = 0x01,
    MBC1RAM = 0x02,
    MBC1RAMBATTERY = 0x03,
    MBC2 = 0x05,
    MBC2BATTERY = 0x06,
    ROMRAM = 0x08,
    ROMRAMBATTERY = 0x09,
    MMMO1 = 0xB,
    MMMO1RAM = 0xC,
    MMMO1RAMBATTERY = 0xD,
    MBC3TIMERBATTERY = 0xF,
    MBC3TIMERRAMBATTERY = 0x10,
    MBC3 = 0x11,
    MBC3RAM = 0x12,
    MBC3RAMBATTERY = 0x13,
    MBC5 = 0x19,
    MBC5RAM = 0x1A,
    MBC5RAMBATTERY = 0x1B,
    MBC5RUMBLE = 0x1C,
    MBC5RUMBLERAM = 0x1D,
    MBC5RUMBLERAMBATTERY = 0x1E,
    MBC6 = 0x20,
    MBC7SENSORRUMBLERAMBATTERY = 0x22,
    POCKETCAMERA = 0xFC,
    BANDAITAMA5 = 0xFD,
    HUC3 = 0xFE,
    HUC1RAMBATTERY = 0xFF
};

class GameboyCPU;
struct Instruction
{
    bool is_cb;
    long pc;
    long opcode;
    long ticks;

    GameboyCPU* cpu;

    void (*exec)(Instruction*);
};

class Memory;
class Video;
class Timer;
class GameboyCPU
{
private:
    Registers registers;
    Memory* memory;
    Video* video;
    Timer* timer;
    Instruction* instruction;
    GxEPD_Class* display;
    long cycles;

    void tick(long num_cycles);
    void fetch_and_decode();

    bool enable_interrupts;
    bool wait_for_interrupt;
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

    uint8_t special_register_read(SpecialRegisterType reg);
    void special_register_write(SpecialRegisterType reg, uint8_t data);

    void request_interrupt(Interrupt interrupt);
    void fire_interrupt(Interrupt interrupt);
    void check_interrupt();

    void set_enable_interrupts(bool enabled);
    void set_wait_for_interrupt(bool enabled);

    static GameboyCPU* instance;

    bool bootstrap_completed;
};

#endif
