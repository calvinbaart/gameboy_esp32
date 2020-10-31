#include "gameboy_cpu.h"
#include "memory.h"
#include "video.h"
#include "timer.h"
#include "opcodes.h"

GameboyCPU* GameboyCPU::instance = nullptr;

GameboyCPU::GameboyCPU(GxEPD_Class* display) : registers(), video(this, display), timer(this), memory(this)
{
    instruction = new Instruction();
    memset(instruction, 0, sizeof(Instruction));
    memset(&registers, 0, sizeof(Registers));

    registers.P1 = 0xFF;
    registers.IF = 0;

    registers.SP = 0xFFFE;
    registers.BC = 0x0013;
    registers.DE = 0x00D8;
    registers.HL = 0x014D;

    joypad_state = 0xFF;

    bootstrap_completed = false;
    instance = this;
}

void GameboyCPU::tick(long num_cycles)
{
    cycles += num_cycles;
    video.tick(num_cycles);
    timer.tick(num_cycles);
    tick_input(num_cycles);
}

void GameboyCPU::set_bios(File bios)
{
    memory.set_bios(bios);
}

void GameboyCPU::set_rom(File rom)
{
    memory.set_rom(rom);
}

void GameboyCPU::fetch_and_decode()
{
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
        Serial.printf("Invalid opcode: 0x%02X, is_cb=%d, pc=0x%04X\n", instruction->opcode, (int)instruction->is_cb, registers.PC);
        return false;
    }

    long before_cycles = cycles;
    long before_time = millis();

    instruction->exec(instruction->opcode, this, instruction);

    if (instruction->ticks != 0)
    {
        tick(instruction->ticks);
    }

    long delta_cycles = cycles - before_cycles;
    long delta_time = millis() - before_time;
    long expected_delta_time = ((delta_cycles / 4.0f) / 4194304.0f) * 1000.0f;

    if (delta_time < expected_delta_time) {
        float percentage = ((float)delta_time) / expected_delta_time;
        Serial.printf("opcode 0x%02X runs %.02fx slower, (time=%d, expected=%d)\n", instruction->opcode, percentage, delta_time, expected_delta_time);
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

    long result = memory.read8(pc);
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

void GameboyCPU::clear_flags()
{
    registers.F = 0;
}

void GameboyCPU::set_flag(Flags flag, bool condition)
{
    if (condition) {
        enable_flag(flag);
    } else {
        disable_flag(flag);
    }
}

void GameboyCPU::enable_flag(Flags flag)
{
    registers.F = registers.F | flag;
}

void GameboyCPU::disable_flag(Flags flag)
{
    registers.F = registers.F & ~flag;
}

bool GameboyCPU::is_flag_set(Flags flag)
{
    return (registers.F & flag) != 0;
}

void GameboyCPU::push_stack(long val)
{
    auto sp = registers.SP;

    sp--;
    memory.write8(sp, val >> 8);
    sp--;
    memory.write8(sp, val & 0xFF);

    registers.SP = sp;
}

long GameboyCPU::pop_stack()
{
    auto sp = registers.SP;

    auto val1 = memory.read8(sp);
    sp++;
    auto val2 = memory.read8(sp);
    sp++;

    registers.SP = sp;

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

    switch (reg)
    {
        case SpecialRegisterType::SC:
            if (data == 0x81) {
                if (registers.SB == 10) {
                    Serial.print("\n");
                } else {
                    Serial.print((char)registers.SB);
                }
            }
            break;
    }
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
    registers.PC = 0x0040 + (interrupt * 8);
}

void GameboyCPU::set_enable_interrupts(bool enabled)
{
    enable_interrupts = enabled;
}

void GameboyCPU::set_wait_for_interrupt(bool enabled)
{
    wait_for_interrupt = enabled;
}

void GameboyCPU::key_state(Key key, bool pressed)
{
    if (pressed)
    {
        joypad_state &= ~(1 << ((int)key));
    } else {
        joypad_state |= 1 << ((int)key);
    }
}

void GameboyCPU::tick_input(long cycles)
{
    long current = registers.P1 & 0xF0;
    long top_joypad, bottom_joypad;

    switch (current & 0x30)
    {
        case 0x10:
            top_joypad = (joypad_state >> 4) & 0x0F;
            current |= top_joypad;
            break;
        
        case 0x20:
            bottom_joypad = joypad_state & 0x0F;
            current |= bottom_joypad;
            break;
        
        case 0x30:
            current |= 0x0F;
            break;
    }

    if ((registers.P1 & ~current & 0x0F) != 0) {
        Serial.println("requesting interrupt");
        request_interrupt(Interrupt::JoypadInterrupt);
    }

    registers.P1 = current;
}