#include "gameboy_cpu.h"
#include "memory.h"
#include "video.h"
#include "timer.h"
#include "opcodes.h"

GameboyCPU* GameboyCPU::instance = nullptr;

GameboyCPU::GameboyCPU(GxEPD_Class* display) : registers()
{
    memory = new Memory(this);
    video = new Video(this, display);
    timer = new Timer(this);
    instruction = new Instruction();
    memset(instruction, 0, sizeof(Instruction));

    instruction->cpu = this;

    this->display = display;

    memset(&registers, 0, sizeof(Registers));

    registers.P1 = 0xFF;
    registers.IF = 0;

    set(RegisterType::SP, 0xFFFE);
    set(RegisterType::BC, 0x0013);
    set(RegisterType::DE, 0x00D8);
    set(RegisterType::HL, 0x014D);

    bootstrap_completed = false;
    instance = this;
}

void GameboyCPU::tick(long num_cycles)
{
    cycles += num_cycles;
    video->tick(num_cycles);
    timer->tick(num_cycles);
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

void GameboyCPU::fetch_and_decode()
{
    instruction->pc = registers.PC;

    instruction->opcode = read_u8();
    instruction->is_cb = instruction->opcode == 0xCB;

    if (instruction->is_cb)
    {
        instruction->opcode = read_u8();

        instruction->ticks = cb_opcode_ticks[instruction->opcode];
        instruction->exec = cb_opcodes[instruction->opcode];

        return;
    }

    instruction->ticks = opcode_ticks[instruction->opcode];
    instruction->exec = opcodes[instruction->opcode];
}

bool GameboyCPU::step()
{
    if (wait_for_interrupt)
    {
        cycles += 4;
        tick(4);
        check_interrupt();

        if (wait_for_interrupt)
        {
            return true;
        }
    }

    fetch_and_decode();

    if (instruction->exec == nullptr)
    {
        char hex[5];
        snprintf(hex, sizeof(hex), "0x%02X", instruction->opcode);

        hex[4] = 0;

        if (instruction->is_cb)
        {
            display->println("Invalid CB opcode: " + String(hex));
        } 
        else 
        {
            display->println("Invalid opcode: " + String(hex));
        }

        display->updateWindow(0, 0, display->width(), display->height());

        return false;
    }

    if (instruction->exec != nullptr)
    {
        instruction->exec(instruction);
    }

    if (instruction->ticks != 0)
    {
        tick(instruction->ticks);
    }

    check_interrupt();
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

Video* GameboyCPU::get_video()
{
    return video;
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

void GameboyCPU::check_interrupt()
{
    if (!enable_interrupts)
    {
        return;
    }

    uint8_t interrupt_flag = registers.IF & registers.IE;

    if (interrupt_flag & (1 << Interrupt::VBlankInterrupt))
    {
        fire_interrupt(Interrupt::VBlankInterrupt);
        registers.IF &= ~(1 << Interrupt::VBlankInterrupt);
    }
    else if (interrupt_flag & (1 << Interrupt::LCDStatInterrupt))
    {
        fire_interrupt(Interrupt::LCDStatInterrupt);
        registers.IF &= ~(1 << Interrupt::LCDStatInterrupt);
    }
    else if (interrupt_flag & (1 << Interrupt::TimerInterrupt))
    {
        fire_interrupt(Interrupt::TimerInterrupt);
        registers.IF &= ~(1 << Interrupt::TimerInterrupt);
    }
    else if (interrupt_flag & (1 << Interrupt::SerialInterrupt))
    {
        fire_interrupt(Interrupt::SerialInterrupt);
        registers.IF &= ~(1 << Interrupt::SerialInterrupt);
    }
    else if (interrupt_flag & (1 << Interrupt::JoypadInterrupt))
    {
        fire_interrupt(Interrupt::JoypadInterrupt);
        registers.IF &= ~(1 << Interrupt::JoypadInterrupt);
    }
}

uint8_t GameboyCPU::special_register_read(SpecialRegisterType reg)
{
    uint8_t val = 0xFF;

    switch (reg)
    {
        case SpecialRegisterType::P1:
            val = registers.P1 | 0xC0;
            break;
        
        case SpecialRegisterType::SB:
            break;
        
        case SpecialRegisterType::SC:
            val = 0xFE;
            break;
        
        case SpecialRegisterType::IF:
            val = registers.IF | 0xE0;
            break;

        case SpecialRegisterType::IE:
            val = registers.IE;
            break;
    }

    return val;
}

void GameboyCPU::special_register_write(SpecialRegisterType reg, uint8_t data)
{
    switch (reg)
    {
        case SpecialRegisterType::P1:
            registers.P1 = data;
            break;

        case SpecialRegisterType::SB:
            registers.SB = data;
            break;

        case SpecialRegisterType::SC:
            registers.SC = data;
            break;

        case SpecialRegisterType::IF:
            registers.IF = data;
            break;

        case SpecialRegisterType::IE:
            registers.IE = data;
            break;
    }

//    switch (register)
//    {
//        case SpecialRegisterType::SC:
//            if (val === 0x81) {
//                if (this._specialRegisters[SpecialRegister.SB] === 10) {
//                    if (this._debugString.trim().length > 0) {
//                        console.log(this._debugString);
//                    }
//
//                    this._debugString = "";
//                } else {
//                    this._debugString += String.fromCharCode(this._specialRegisters[SpecialRegister.SB]);
//                }
//            } else {
//                if (!this._serialStarted && this._network.isConnected()) {
//                    this._serialStarted = (val & (1 << 7)) ? true : false;
//                    this._serialClock = (val & (1 << 0)) ? 1 : 0;
//                }
//            }
//            break;
//        
//        case SpecialRegisterType::SB:
//            if (this._serialStarted && this._network.isConnected()) {
//                this._network.write(val);
//                this._specialRegisters[SpecialRegister.SB] = this._network.read();
//            }
//            break;
//    }
}

void GameboyCPU::request_interrupt(Interrupt interrupt)
{
    long mask = 1 << interrupt;

    if (mask & registers.IE) {
        wait_for_interrupt = false;
    }

    registers.IF |= mask;
}

void GameboyCPU::fire_interrupt(Interrupt interrupt)
{
    enable_interrupts = false;

    push_stack(registers.PC);
    set(RegisterType::PC, 0x0040 + (interrupt * 8));
}

void GameboyCPU::set_enable_interrupts(bool enabled)
{
    enable_interrupts = enabled;
}

void GameboyCPU::set_wait_for_interrupt(bool enabled)
{
    wait_for_interrupt = enabled;
}
