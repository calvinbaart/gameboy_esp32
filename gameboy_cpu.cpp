#include "gameboy_cpu.h"
#include "memory.h"
#include "video.h"
#include "opcodes.h"

GameboyCPU* GameboyCPU::instance = nullptr;

GameboyCPU::GameboyCPU(GxEPD_Class* display) : registers()
{
    memory = new Memory(this);
    video = new Video(this, display);
    this->display = display;

    instance = this;
}

void GameboyCPU::tick(long num_cycles)
{
    cycles += num_cycles;
    video->tick(num_cycles);
}

void GameboyCPU::set_bios(File bios)
{
    memory->set_bios(bios);
}

void GameboyCPU::set_rom(File rom)
{
    memory->set_rom(rom);
}

void GameboyCPU::cycle(long num)
{
    tick(num);
}

Instruction GameboyCPU::fetch_and_decode()
{
    Instruction instruction;
    instruction.cpu = this;
    instruction.pc = registers.PC;

    instruction.opcode = read_u8();
    instruction.is_cb = instruction.opcode == 0xCB;

    if (instruction.is_cb)
    {
        instruction.opcode = read_u8();

        instruction.ticks = cb_opcode_ticks[instruction.opcode];
        instruction.exec = cb_opcodes[instruction.opcode];

        return instruction;
    }

    instruction.ticks = opcode_ticks[instruction.opcode];
    instruction.exec = opcodes[instruction.opcode];

    return instruction;
}

bool GameboyCPU::step()
{
    // if (this._waitForInterrupt)
    // {
    //     this._cycles += 4;
    //     this._tickInternal(4);
    //     this.checkInterrupt();

    //     if (this._waitForInterrupt)
    //     {
    //         return true;
    //     }
    // }

    Instruction instruction = fetch_and_decode();

    if (instruction.exec == nullptr)
    {
        char hex[5];
        snprintf(hex, sizeof(hex), "0x%02X", instruction.opcode);

        hex[4] = 0;

        if (instruction.is_cb) {
            display->println("Invalid CB opcode: " + String(hex));
        } 
        else 
        {
            display->println("Invalid opcode: " + String(hex));
        }

        display->updateWindow(0, 0, display->width(), display->height());

        return false;
    }

    if (instruction.exec != nullptr)
    {
        instruction.exec(instruction);
    }

    if (instruction.ticks != 0)
    {
        tick(instruction.ticks);
    }

    // this.checkInterrupt();
    return true;
}

long GameboyCPU::get_cycles()
{
    return cycles;
}

long GameboyCPU::read_u8()
{
    auto pc = registers.PC;

    long result = memory->read8(pc);
    pc++;

    registers.PC = pc;

    return result;
}

long GameboyCPU::read_u16()
{
    long result1 = read_u8();
    long result2 = read_u8();

    return ((result2 & 0xFF) << 8) | (result1 & 0xFF);
}


long GameboyCPU::read_s8()
{
    long num_unsigned = read_u8();
    long msb_mask = 1 << (8 - 1);

    return (num_unsigned ^ msb_mask) - msb_mask;
}

long GameboyCPU::read_s16()
{
    long num_unsigned = read_u16();
    long msb_mask = 1 << (16 - 1);

    return (num_unsigned ^ msb_mask) - msb_mask;
}

long GameboyCPU::increment(RegisterType reg, long num)
{
    long tmp = get(reg);
    tmp += num;

    return set(reg, tmp);
}

long GameboyCPU::decrement(RegisterType reg, long num)
{
    long tmp = get(reg);
    tmp -= num;

    return set(reg, tmp);
}

Memory* GameboyCPU::get_memory()
{
    return memory;
}

RegisterType GameboyCPU::read_register_type(long val, bool useAF)
{
    switch (val & 0x03)
    {
        case 0x00:
            return RegisterType::BC;

        case 0x01:
            return RegisterType::DE;

        case 0x02:
            return RegisterType::HL;

        case 0x03:
            return useAF ? RegisterType::AF : RegisterType::SP;
    }
}

RegisterType GameboyCPU::read_byte_register_type(long val)
{
    switch (val & 0x07)
    {
        case 0x00:
            return RegisterType::B;

        case 0x01:
            return RegisterType::C;

        case 0x02:
            return RegisterType::D;

        case 0x03:
            return RegisterType::E;

        case 0x04:
            return RegisterType::H;

        case 0x05:
            return RegisterType::L;

        case 0x06:
            return RegisterType::F;

        case 0x07:
            return RegisterType::A;
    }
}

long GameboyCPU::set(RegisterType reg, long value)
{
    switch (reg)
    {
        case RegisterType::A:
            registers.A = value;
            return registers.A;

        case RegisterType::B:
            registers.B = value;
            return registers.B;

        case RegisterType::C:
            registers.C = value;
            return registers.C;

        case RegisterType::D:
            registers.D = value;
            return registers.D;

        case RegisterType::E:
            registers.E = value;
            return registers.E;

        case RegisterType::H:
            registers.H = value;
            return registers.H;

        case RegisterType::L:
            registers.L = value;
            return registers.L;

        case RegisterType::F:
            registers.F = value;
            return registers.F;

        case RegisterType::AF:
            registers.AF = value;
            registers.A = registers.AF >> 8;
            registers.F = registers.AF & 0xFF;

            return registers.AF;

        case RegisterType::SP:
            registers.SP = value;
            return registers.SP;

        case RegisterType::PC:
            registers.PC = value;
            return registers.PC;

        case RegisterType::BC:
            registers.BC = value;
            registers.B = registers.BC >> 8;
            registers.C = registers.BC & 0xFF;
            return registers.BC;

        case RegisterType::DE:
            registers.DE = value;
            registers.D = registers.DE >> 8;
            registers.E = registers.DE & 0xFF;
            return registers.DE;

        case RegisterType::HL:
            registers.HL = value;
            registers.H = registers.HL >> 8;
            registers.L = registers.HL & 0xFF;
            return registers.HL;
    }
}

long GameboyCPU::get(RegisterType reg)
{
    switch (reg) 
    {
        case RegisterType::A:
            return registers.A;
        
        case RegisterType::B:
            return registers.B;

        case RegisterType::C:
            return registers.C;

        case RegisterType::D:
            return registers.D;

        case RegisterType::E:
            return registers.E;

        case RegisterType::H:
            return registers.H;

        case RegisterType::L:
            return registers.L;

        case RegisterType::F:
            return registers.F;
        
        case RegisterType::AF:
            return (((long)registers.A) << 8) | registers.F;

        case RegisterType::SP:
            return registers.SP;
        
        case RegisterType::PC:
            return registers.PC;
        
        case RegisterType::BC:
            return (((long)registers.B) << 8) | registers.C;

        case RegisterType::DE:
            return (((long)registers.D) << 8) | registers.E;

        case RegisterType::HL:
            return (((long)registers.H) << 8) | registers.L;
    }
}

void GameboyCPU::clear_flags()
{
    set(RegisterType::F, 0);
}

void GameboyCPU::enable_flag(Flags flag)
{
    set(RegisterType::F, get(RegisterType::F) | flag);
}

void GameboyCPU::disable_flag(Flags flag)
{
    set(RegisterType::F, get(RegisterType::F) & ~flag);
}

bool GameboyCPU::is_flag_set(Flags flag)
{
    return (get(RegisterType::F) & flag) != 0;
}

void GameboyCPU::push_stack(long val)
{
    auto sp = get(RegisterType::SP);

    sp--;
    memory->write8(sp, val >> 8);
    sp--;
    memory->write8(sp, val & 0xFF);

    set(RegisterType::SP, sp);
}

long GameboyCPU::pop_stack()
{
    auto sp = get(RegisterType::SP);

    auto val1 = memory->read8(sp);
    sp++;
    auto val2 = memory->read8(sp);
    sp++;

    set(RegisterType::SP, sp);

    return (val2 << 8) | val1;
}
