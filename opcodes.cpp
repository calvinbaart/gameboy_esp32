#include "opcodes.h"
#include "gameboy_cpu.h"
#include "memory.h"

void toggle_zero_flag(GameboyCPU* cpu, long result)
{
    if ((result & 0xFF) == 0)
    {
        cpu->enable_flag(Flags::ZeroFlag);
    }
    else
    {
        cpu->disable_flag(Flags::ZeroFlag);
    }
}

void BIT_Impl(RegisterType reg, long bit, GameboyCPU* cpu)
{
    long value = 0;
    
    if (reg == RegisterType::None)
    {
        value = cpu->get_memory()->read8(cpu->get(RegisterType::HL));

        cpu->cycle(4);
    }
    else
    {
        value = cpu->get(reg);
    }

    toggle_zero_flag(cpu, ((value >> bit) & 0x01));
    cpu->enable_flag(Flags::HalfCarryFlag);
    cpu->disable_flag(Flags::AddSubFlag);

    cpu->cycle(4);
}

void CP(long val, GameboyCPU* cpu)
{
    cpu->clear_flags();
    cpu->enable_flag(Flags::AddSubFlag);

    auto A = cpu->get(RegisterType::A);

    if (val == A)
    {
        cpu->enable_flag(Flags::ZeroFlag);
    }

    if (A < val)
    {
        cpu->enable_flag(Flags::CarryFlag);
    }

    if (((A - val) & 0xF) > (A & 0xF))
    {
        cpu->enable_flag(Flags::HalfCarryFlag);
    }
}

void SUB(long reg, bool use_carry, GameboyCPU* cpu, bool is_number)
{
    long val = 0;

    cpu->enable_flag(Flags::AddSubFlag);

    if (is_number)
    {
        val = reg;
    }
    else if (reg == RegisterType::None)
    {
        auto tmp = cpu->get_memory()->read8(cpu->get(RegisterType::HL));

        val = tmp;
    }
    else
    {
        val = cpu->get((RegisterType)reg);
    }

    auto A = cpu->get(RegisterType::A);
    auto extra = (use_carry && cpu->is_flag_set(Flags::CarryFlag)) ? 1 : 0;
    auto result = A - val - extra;

    if (result < 0)
    {
        cpu->enable_flag(Flags::CarryFlag);
    }
    else
    {
        cpu->disable_flag(Flags::CarryFlag);
    }

    if ((A & 0xF) - (val & 0xF) - extra < 0) {
        cpu->enable_flag(Flags::HalfCarryFlag);
    } else {
        cpu->disable_flag(Flags::HalfCarryFlag);
    }

    cpu->set(RegisterType::A, result);
    toggle_zero_flag(cpu, result);
}

void ADD(long reg, bool add_carry, GameboyCPU* cpu, bool is_number)
{
    long val = 0;

    if (is_number)
    {
        val = reg;
    }
    else if (reg == RegisterType::None)
    {
        val = cpu->get_memory()->read8(cpu->get(RegisterType::HL));
    } 
    else
    {
        val = cpu->get((RegisterType)reg);
    }

    auto A = cpu->get(RegisterType::A);
    auto extra = (add_carry && cpu->is_flag_set(Flags::CarryFlag)) ? 1 : 0;
    auto result = A + val + extra;

    if (result > 0xFF)
    {
        cpu->enable_flag(Flags::CarryFlag);
    }
    else
    {
        cpu->disable_flag(Flags::CarryFlag);
    }

    if ((A & 0xF) + (val & 0xF) + extra > 0xF) {
        cpu->enable_flag(Flags::HalfCarryFlag);
    } else {
        cpu->disable_flag(Flags::HalfCarryFlag);
    }

    cpu->set(RegisterType::A, result);
    toggle_zero_flag(cpu, result);

    cpu->disable_flag(Flags::AddSubFlag);
}

void ADD_16(RegisterType register1, long register2, GameboyCPU* cpu, bool is_number)
{
    cpu->clear_flags();
    
    long val = 0;
    if (!is_number)
    {
        val = cpu->get((RegisterType)register2);
    }
    else
    {
        val = register2;
    }

    auto value1 = cpu->get(register1);
    auto result = value1 + val;

    if (((value1 ^ val ^ (result & 0xFFFF)) & 0x100) == 0x100)
    {
        cpu->enable_flag(Flags::CarryFlag);
    }

    if (((value1 ^ val ^ (result & 0xFFFF)) & 0x10) == 0x10)
    {
        cpu->enable_flag(Flags::HalfCarryFlag);
    }

    cpu->set(register1, result);
}

void SWAP(RegisterType reg, GameboyCPU* cpu)
{
    cpu->clear_flags();

    long result = 0;
    if (reg == RegisterType::None)
    {
        auto HL = cpu->get(RegisterType::HL);
        auto value = cpu->get_memory()->read8(HL);
        
        cpu->cycle(4);

        result = ((value & 0x0F) << 4) | ((value & 0xF0) >> 4);

        cpu->get_memory()->write8(HL, result);

        cpu->cycle(4);
    } 
    else
    {
        auto data = cpu->get(reg);

        result = ((data & 0x0F) << 4) | ((data & 0xF0) >> 4);
        cpu->set(reg, result);
    }

    toggle_zero_flag(cpu, result);
    cpu->cycle(4);
}

void SRL(RegisterType reg, GameboyCPU* cpu)
{
    cpu->clear_flags();

    long result = 0;

    if (reg == RegisterType::None) {
        result = cpu->get_memory()->read8(cpu->get(RegisterType::HL));

        cpu->cycle(4);
    } else {
        result = cpu->get(reg);
    }

    if ((result & 0x01) != 0) {
        cpu->enable_flag(Flags::CarryFlag);
    }

    result >>= 1;

    if (reg == RegisterType::None) {
        cpu->get_memory()->write8(cpu->get(RegisterType::HL), result);

        cpu->cycle(4);
    } else {
        cpu->set(reg, result);
    }
    
    toggle_zero_flag(cpu, result);

    cpu->cycle(4);
}

void LD_0x01x11x21x31(Instruction* instruction)
{
    auto val = instruction->cpu->read_u16();
    auto reg = instruction->cpu->read_register_type(instruction->opcode >> 4, false);

    instruction->cpu->set(reg, val);
}

void XOR_0xA9(Instruction* instruction)
{
    auto reg = instruction->cpu->read_byte_register_type(instruction->opcode);
    auto result = instruction->cpu->get(RegisterType::A) ^ instruction->cpu->get(reg);

    instruction->cpu->clear_flags();
    instruction->cpu->set(RegisterType::A, result);

    toggle_zero_flag(instruction->cpu, result);
}

void LD_0x32(Instruction* instruction)
{
    instruction->cpu->get_memory()->write8(instruction->cpu->get(RegisterType::HL), instruction->cpu->get(RegisterType::A));
    instruction->cpu->decrement(RegisterType::HL);
}

void JR_0x20(Instruction* instruction)
{
    auto relative = instruction->cpu->read_s8();
    bool check = false;

    switch ((instruction->opcode >> 3) & 0x03)
    {
        case 0x00:
            check = !instruction->cpu->is_flag_set(Flags::ZeroFlag);
            break;

        case 0x01:
            check = instruction->cpu->is_flag_set(Flags::ZeroFlag);
            break;

        case 0x02:
            check = !instruction->cpu->is_flag_set(Flags::CarryFlag);
            break;

        case 0x03:
            check = instruction->cpu->is_flag_set(Flags::CarryFlag);
            break;
    }

    if (check)
    {
        instruction->cpu->increment(RegisterType::PC, relative);
        instruction->ticks += 4;
    }
}

void LD_0x06(Instruction* instruction)
{
    auto reg = instruction->cpu->read_byte_register_type(instruction->opcode >> 3);
    auto val = instruction->cpu->read_u8();

    instruction->cpu->set(reg, val);
}

void LD_0xE2(Instruction* instruction)
{
    instruction->cpu->get_memory()->write8(0xFF00 + instruction->cpu->get(RegisterType::C), instruction->cpu->get(RegisterType::A));
}

void LD_0x70(Instruction* instruction)
{
    auto reg = instruction->cpu->read_byte_register_type(instruction->opcode);

    instruction->cpu->get_memory()->write8(instruction->cpu->get(RegisterType::HL), instruction->cpu->get(reg));
}

void INC_0x04x0Cx14x1Cx24x2Cx3C(Instruction* instruction)
{
    auto reg = instruction->cpu->read_byte_register_type(instruction->opcode >> 3);

    instruction->cpu->disable_flag(Flags::ZeroFlag);
    instruction->cpu->disable_flag(Flags::AddSubFlag);

    instruction->cpu->increment(reg);

    auto val = instruction->cpu->get(reg);

    if ((val & 0x0F) == 0x00)
    {
        instruction->cpu->enable_flag(Flags::HalfCarryFlag);
    }
    else
    {
        instruction->cpu->disable_flag(Flags::HalfCarryFlag);
    }

    toggle_zero_flag(instruction->cpu, val);
}

void LDH_0xE0(Instruction* instruction)
{
    instruction->cpu->cycle(4);

    auto pos = 0xFF00 + instruction->cpu->read_u8();

    instruction->cpu->get_memory()->write8(pos, instruction->cpu->get(RegisterType::A));

    instruction->cpu->cycle(4);
    instruction->cpu->cycle(4);
}

void LD_0x1A(Instruction* instruction)
{
    instruction->cpu->set(RegisterType::A, instruction->cpu->get_memory()->read8(instruction->cpu->get(RegisterType::DE)));
}

void CALL_0xCD(Instruction* instruction)
{
    auto addr = instruction->cpu->read_u16();

    instruction->cpu->push_stack(instruction->cpu->get(RegisterType::PC));
    instruction->cpu->set(RegisterType::PC, addr);
}

void LD_0x40(Instruction* instruction)
{
    auto r1 = instruction->cpu->read_byte_register_type(instruction->opcode >> 3);
    auto r2 = instruction->cpu->read_byte_register_type(instruction->opcode);

    instruction->cpu->set(r1, instruction->cpu->get(r2));
}

void PUSH_0xC5(Instruction* instruction)
{
    auto reg = instruction->cpu->read_register_type(instruction->opcode >> 4, true);

    instruction->cpu->push_stack(instruction->cpu->get(reg));
}

void POP_0xC1(Instruction* instruction)
{
    auto reg = instruction->cpu->read_register_type(instruction->opcode >> 4, true);

    instruction->cpu->set(reg, instruction->cpu->pop_stack());

    if (((instruction->opcode >> 4) & 0x03) == 0x03) {
        instruction->cpu->set(reg, instruction->cpu->get(reg) & 0xFFF0);
    }
}

void DEC_0x05x0Dx15x1Dx25x2Dx3D(Instruction* instruction)
{
    auto reg = instruction->cpu->read_byte_register_type(instruction->opcode >> 3);

    instruction->cpu->enable_flag(Flags::AddSubFlag);
    instruction->cpu->disable_flag(Flags::ZeroFlag);

    instruction->cpu->decrement(reg);

    auto result = instruction->cpu->get(reg);
    if ((result & 0x0F) == 0x0F) {
        instruction->cpu->enable_flag(Flags::HalfCarryFlag);
    } else {
        instruction->cpu->disable_flag(Flags::HalfCarryFlag);
    }

    toggle_zero_flag(instruction->cpu, result);
}

void LD_0x22(Instruction* instruction)
{
    instruction->cpu->get_memory()->write8(instruction->cpu->get(RegisterType::HL), instruction->cpu->get(RegisterType::A));
    instruction->cpu->increment(RegisterType::HL);
}

void INC_0x03x13x23x33(Instruction* instruction)
{
    auto reg = instruction->cpu->read_register_type(instruction->opcode >> 4, false);
    instruction->cpu->increment(reg);
}

void RET_0xC9(Instruction* instruction)
{
    instruction->cpu->set(RegisterType::PC, instruction->cpu->pop_stack());
}

void CP_0xFE(Instruction* instruction)
{
    CP(instruction->cpu->read_u8(), instruction->cpu);
}

void LD_0xEA(Instruction* instruction)
{
    instruction->cpu->cycle(4);
    instruction->cpu->cycle(4);

    auto addr = instruction->cpu->read_u16();

    instruction->cpu->get_memory()->write8(addr, instruction->cpu->get(RegisterType::A));

    instruction->cpu->cycle(4);
    instruction->cpu->cycle(4);
}

void LDH_0xF0(Instruction* instruction)
{
    instruction->cpu->cycle(4);

    auto pos = 0xFF00 + instruction->cpu->read_u8();

    instruction->cpu->set(RegisterType::A, instruction->cpu->get_memory()->read8(pos));

    instruction->cpu->cycle(4);
    instruction->cpu->cycle(4);
}

void SUB_0x90(Instruction* instruction)
{
    SUB(instruction->cpu->read_byte_register_type(instruction->opcode), false, instruction->cpu, false);
}

void JR_0x18(Instruction* instruction)
{
    auto relative = instruction->cpu->read_s8();

    instruction->cpu->increment(RegisterType::PC, relative);
}

void CP_0xBE(Instruction* instruction)
{
    CP(instruction->cpu->get_memory()->read8(instruction->cpu->get(RegisterType::HL)), instruction->cpu);
}

void ADD_0x86(Instruction* instruction)
{
    ADD(RegisterType::None, false, instruction->cpu, false);
}

void RL_0x11(Instruction* instruction)
{
    instruction->cpu->cycle(4);

    auto reg = instruction->cpu->read_byte_register_type(instruction->opcode);
    auto result = 0;

    if ((instruction->opcode & 0x7) == 6) {
        result = instruction->cpu->get_memory()->read8(instruction->cpu->get(RegisterType::HL));

        instruction->cpu->cycle(4);
    } else {
        result = instruction->cpu->get(reg);
    }

    auto carry = instruction->cpu->is_flag_set(Flags::CarryFlag) ? 0x01 : 0x00;

    instruction->cpu->clear_flags();

    if ((result & 0x80) != 0) {
        instruction->cpu->enable_flag(Flags::CarryFlag);
    }

    result <<= 1;
    result |= carry;

    if ((instruction->opcode & 0x7) == 6) {
        instruction->cpu->get_memory()->write8(instruction->cpu->get(RegisterType::HL), result);

        instruction->cpu->cycle(4);
    } else {
        instruction->cpu->set(reg, result);
    }

    toggle_zero_flag(instruction->cpu, result);
    instruction->cpu->cycle(4);
}

void RLA_0x17(Instruction* instruction)
{
    auto reg = instruction->cpu->read_byte_register_type(instruction->opcode);
    auto carry = instruction->cpu->is_flag_set(Flags::CarryFlag) ? 1 : 0;
    auto result = instruction->cpu->get(reg);

    instruction->cpu->clear_flags();

    if ((result & 0x80) != 0) {
        instruction->cpu->enable_flag(Flags::CarryFlag);
    }

    result <<= 1;
    result |= carry;

    instruction->cpu->set(reg, result);
}

void BIT_0x7C(Instruction* instruction)
{
    instruction->cpu->cycle(4);

    auto reg = instruction->cpu->read_byte_register_type(instruction->opcode);
    auto bit = (instruction->opcode & 0b00111000) >> 3;

    if ((instruction->opcode & 0x7) == 6)
    {
        BIT_Impl(RegisterType::None, bit, instruction->cpu);
    }
    else
    {
        BIT_Impl(reg, bit, instruction->cpu);
    }
}

void JP_0xC3(Instruction* instruction)
{
    auto addr = instruction->cpu->read_u16();

    instruction->cpu->set(RegisterType::PC, addr);
}

void DI_0xF3(Instruction* instruction)
{
    instruction->cpu->set_enable_interrupts(false);
}

void LD_0x36(Instruction* instruction)
{
    instruction->cpu->cycle(4);

    auto val = instruction->cpu->read_u8();

    instruction->cpu->get_memory()->write8(instruction->cpu->get(RegisterType::HL), val);

    instruction->cpu->cycle(4);
    instruction->cpu->cycle(4);
}

void LD_0x2A(Instruction* instruction)
{
    instruction->cpu->set(RegisterType::A, instruction->cpu->get_memory()->read8(instruction->cpu->get(RegisterType::HL)));
    instruction->cpu->increment(RegisterType::HL);
}

void DEC_0x0B(Instruction* instruction)
{
    auto reg = instruction->cpu->read_register_type(instruction->opcode >> 4, false);

    instruction->cpu->decrement(reg);
}

void OR_0xB0(Instruction* instruction)
{
    auto reg = instruction->cpu->read_byte_register_type(instruction->opcode);
    auto result = instruction->cpu->get(RegisterType::A) | instruction->cpu->get(reg);

    instruction->cpu->clear_flags();
    instruction->cpu->set(RegisterType::A, result);

    toggle_zero_flag(instruction->cpu, result);
}

void EI_0xFB(Instruction* instruction)
{
    instruction->cpu->set_enable_interrupts(true);
}

void AND_0xA0(Instruction* instruction)
{
    auto reg = instruction->cpu->read_byte_register_type(instruction->opcode);
    auto result = instruction->cpu->get(RegisterType::A) & instruction->cpu->get(reg);

    instruction->cpu->clear_flags();
    instruction->cpu->set(RegisterType::A, result);

    toggle_zero_flag(instruction->cpu, result);

    instruction->cpu->enable_flag(Flags::HalfCarryFlag);
}

void RET_0xC0(Instruction* instruction)
{
    bool check = false;

    switch ((instruction->opcode >> 3) & 0x03)
    {
        case 0x00:
            check = !instruction->cpu->is_flag_set(Flags::ZeroFlag);
            break;

        case 0x01:
            check = instruction->cpu->is_flag_set(Flags::ZeroFlag);
            break;

        case 0x02:
            check = !instruction->cpu->is_flag_set(Flags::CarryFlag);
            break;

        case 0x03:
            check = instruction->cpu->is_flag_set(Flags::CarryFlag);
            break;
    }

    if (check)
    {
        instruction->cpu->set(RegisterType::PC, instruction->cpu->pop_stack());
        instruction->ticks += 12;
    }
}

void LD_0xFA(Instruction* instruction)
{
    instruction->cpu->cycle(4);
    instruction->cpu->cycle(4);

    auto addr = instruction->cpu->read_u16();
    instruction->cpu->set(RegisterType::A, instruction->cpu->get_memory()->read8(addr));

    instruction->cpu->cycle(4);
    instruction->cpu->cycle(4);
}

void INC_0x34(Instruction* instruction)
{
    instruction->cpu->disable_flag(Flags::ZeroFlag);
    instruction->cpu->disable_flag(Flags::AddSubFlag);

    auto HL = instruction->cpu->get(RegisterType::HL);
    auto val = (instruction->cpu->get_memory()->read8(HL) + 1) & 0xFF;

    instruction->cpu->cycle(4);

    toggle_zero_flag(instruction->cpu, val);

    if ((val & 0xF) == 0x00) {
        instruction->cpu->enable_flag(Flags::HalfCarryFlag);
    } else {
        instruction->cpu->disable_flag(Flags::HalfCarryFlag);
    }

    instruction->cpu->get_memory()->write8(HL, val);

    instruction->cpu->cycle(4);
    instruction->cpu->cycle(4);
}

void RETI_0xD9(Instruction* instruction)
{
    instruction->cpu->set(RegisterType::PC, instruction->cpu->pop_stack());
    instruction->cpu->set_enable_interrupts(true);
}

void CPL_0x2F(Instruction* instruction)
{
    instruction->cpu->set(RegisterType::A, instruction->cpu->get(RegisterType::A) ^ 0xFF);

    instruction->cpu->enable_flag(Flags::HalfCarryFlag);
    instruction->cpu->enable_flag(Flags::AddSubFlag);
}

void AND_0xE6(Instruction* instruction)
{
    auto val = instruction->cpu->read_u8();
    auto result = instruction->cpu->get(RegisterType::A) & val;

    instruction->cpu->clear_flags();
    instruction->cpu->set(RegisterType::A, result);

    toggle_zero_flag(instruction->cpu, result);

    instruction->cpu->enable_flag(Flags::HalfCarryFlag);
}

void SWAP_0x37(Instruction* instruction)
{
    instruction->cpu->cycle(4);

    auto reg = instruction->cpu->read_byte_register_type(instruction->opcode);

    if ((instruction->opcode & 0x7) == 6)
    {
        SWAP(RegisterType::None, instruction->cpu);
    } 
    else
    {
        SWAP(reg, instruction->cpu);
    }
}

void RST_0xEF(Instruction* instruction)
{
    auto t = ((instruction->opcode >> 3) & 0x07);
    auto n = t * 0x08;

    instruction->cpu->push_stack(instruction->cpu->get(RegisterType::PC));
    instruction->cpu->set(RegisterType::PC, n);
}

void ADD_0x81(Instruction* instruction)
{
    ADD(instruction->cpu->read_byte_register_type(instruction->opcode), false, instruction->cpu, false);
}

void ADD_0x09(Instruction* instruction)
{
    auto reg = instruction->cpu->read_register_type(instruction->opcode >> 4, false);

    instruction->cpu->disable_flag(Flags::AddSubFlag);

    auto HL = instruction->cpu->get(RegisterType::HL);
    auto data = instruction->cpu->get(reg);

    auto result = (HL + data) & 0xFFFF;

    if (result < HL) {
        instruction->cpu->enable_flag(Flags::CarryFlag);
    } else {
        instruction->cpu->disable_flag(Flags::CarryFlag);
    }

    if ((result ^ HL ^ data) & 0x1000) {
        instruction->cpu->enable_flag(Flags::HalfCarryFlag);
    } else {
        instruction->cpu->disable_flag(Flags::HalfCarryFlag);
    }

    instruction->cpu->set(RegisterType::HL, result);
}

void LD_0x46(Instruction* instruction)
{
    auto reg = instruction->cpu->read_byte_register_type(instruction->opcode >> 3);
    auto val = instruction->cpu->get_memory()->read8(instruction->cpu->get(RegisterType::HL));

    instruction->cpu->set(reg, val);
}

void JP_0xE9(Instruction* instruction)
{
    instruction->cpu->set(RegisterType::PC, instruction->cpu->get(RegisterType::HL));
}

void RES_0x87(Instruction* instruction)
{
    instruction->cpu->cycle(4);

    auto reg = instruction->cpu->read_byte_register_type(instruction->opcode);
    auto bit = (instruction->opcode & 0b00111000) >> 3;

    long result = 0;
    if ((instruction->opcode & 0x7) == 6) {
        result = instruction->cpu->get_memory()->read8(instruction->cpu->get(RegisterType::HL));

        instruction->cpu->cycle(4);
    }
    else
    {
        result = instruction->cpu->get(reg);
    }

    result &= ~(1 << bit);

    if ((instruction->opcode & 0x7) == 6) {
        instruction->cpu->get_memory()->write8(instruction->cpu->get(RegisterType::HL), result);

        instruction->cpu->cycle(4);
    }
    else
    {
        instruction->cpu->set(reg, result);
    }

    instruction->cpu->cycle(4);
}

void LD_0x12(Instruction* instruction)
{
    instruction->cpu->get_memory()->write8(instruction->cpu->get(RegisterType::DE), instruction->cpu->get(RegisterType::A));
}

void JP_0xC2(Instruction* instruction)
{
    auto addr = instruction->cpu->read_u16();
    bool check = false;

    switch ((instruction->opcode >> 3) & 0x03)
    {
        case 0x00:
            check = !instruction->cpu->is_flag_set(Flags::ZeroFlag);
            break;

        case 0x01:
            check = instruction->cpu->is_flag_set(Flags::ZeroFlag);
            break;

        case 0x02:
            check = !instruction->cpu->is_flag_set(Flags::CarryFlag);
            break;

        case 0x03:
            check = instruction->cpu->is_flag_set(Flags::CarryFlag);
            break;
    }

    if (check)
    {
        instruction->cpu->set(RegisterType::PC, addr);
        instruction->ticks += 4;
    }
}

void LD_0x02(Instruction* instruction)
{
    instruction->cpu->get_memory()->write8(instruction->cpu->get(RegisterType::BC), instruction->cpu->get(RegisterType::A));
}

void RLCA_0x07(Instruction* instruction)
{
    auto val = instruction->cpu->get(RegisterType::A);
    instruction->cpu->clear_flags();

    if ((val & 0x80) != 0) {
        instruction->cpu->enable_flag(Flags::CarryFlag);

        val <<= 1;
        val |= 0x01;
    } else {
        val <<= 1;
    }

    instruction->cpu->set(RegisterType::A, val);
}

void LD_0x08(Instruction* instruction)
{
    auto addr = instruction->cpu->read_u16();

    auto SP = instruction->cpu->get(RegisterType::SP);
    instruction->cpu->get_memory()->write8(addr + 0, SP & 0xFF);
    instruction->cpu->get_memory()->write8(addr + 1, (SP >> 8) & 0xFF);
}

void LD_0x0A(Instruction* instruction)
{
    auto val = instruction->cpu->get_memory()->read8(instruction->cpu->get(RegisterType::BC));

    instruction->cpu->set(RegisterType::A, val);
}

void RRCA_0x0F(Instruction* instruction)
{
    auto val = instruction->cpu->get(RegisterType::A);
    instruction->cpu->clear_flags();

    if ((val & 0x01) != 0) {
        instruction->cpu->enable_flag(Flags::CarryFlag);

        val >>= 1;
        val |= 0x80;
    } else {
        val >>= 1;
    }

    instruction->cpu->set(RegisterType::A, val);
}

void RRA_0x1F(Instruction* instruction)
{
    auto reg = instruction->cpu->read_byte_register_type(instruction->opcode);
    auto carry = instruction->cpu->is_flag_set(Flags::CarryFlag) ? 0x80 : 0;
    auto result = instruction->cpu->get(reg);

    instruction->cpu->clear_flags();

    if ((result & 0x01) != 0)
    {
        instruction->cpu->enable_flag(Flags::CarryFlag);
    }

    result >>= 1;
    result |= carry;

    instruction->cpu->set(reg, result);
}

void DAA_0x27(Instruction* instruction)
{
    auto a = instruction->cpu->get(RegisterType::A);

    if (!instruction->cpu->is_flag_set(Flags::AddSubFlag))
    {
        if (instruction->cpu->is_flag_set(Flags::HalfCarryFlag) || (a & 0xF) > 9)
        {
            a += 0x06;
        }

        if (instruction->cpu->is_flag_set(Flags::CarryFlag) || a > 0x9F)
        {
            a += 0x60;
        }
    }
    else
    {
        if (instruction->cpu->is_flag_set(Flags::HalfCarryFlag))
        {
            a = (a - 6) & 0xFF;
        }

        if (instruction->cpu->is_flag_set(Flags::CarryFlag))
        {
            a -= 0x60;
        }
    }

    auto F = instruction->cpu->get(RegisterType::F);
    F &= ~(Flags::HalfCarryFlag | Flags::ZeroFlag);

    if ((a & 0x100) == 0x100)
    {
        F |= Flags::CarryFlag;
    }

    a &= 0xFF;

    if (a == 0)
    {
        F |= Flags::ZeroFlag;
    }

    instruction->cpu->set(RegisterType::F, F);
    instruction->cpu->set(RegisterType::A, a);

    toggle_zero_flag(instruction->cpu, a & 0xFF);
}

void DEC_0x35(Instruction* instruction)
{
    instruction->cpu->enable_flag(Flags::AddSubFlag);
    instruction->cpu->disable_flag(Flags::ZeroFlag);

    auto HL = instruction->cpu->get(RegisterType::HL);
    auto val = (instruction->cpu->get_memory()->read8(HL) - 1) & 0xFF;

    instruction->cpu->cycle(4);

    if ((val & 0xF) == 0xF)
    {
        instruction->cpu->enable_flag(Flags::HalfCarryFlag);
    }
    else
    {
        instruction->cpu->disable_flag(Flags::HalfCarryFlag);
    }

    toggle_zero_flag(instruction->cpu, val);

    instruction->cpu->get_memory()->write8(HL, val);

    instruction->cpu->cycle(4);
    instruction->cpu->cycle(4);
}

void SCF_0x37(Instruction* instruction)
{
    instruction->cpu->disable_flag(Flags::AddSubFlag);
    instruction->cpu->disable_flag(Flags::HalfCarryFlag);
    instruction->cpu->enable_flag(Flags::CarryFlag);
}

void LD_0x3A(Instruction* instruction)
{
    instruction->cpu->set(RegisterType::A, instruction->cpu->get_memory()->read8(instruction->cpu->get(RegisterType::HL)));
    instruction->cpu->decrement(RegisterType::HL);
}

void CCF_0x3F(Instruction* instruction)
{
    instruction->cpu->disable_flag(Flags::AddSubFlag);
    instruction->cpu->disable_flag(Flags::HalfCarryFlag);

    if (instruction->cpu->is_flag_set(Flags::CarryFlag))
    {
        instruction->cpu->disable_flag(Flags::CarryFlag);
    }
    else
    {
        instruction->cpu->enable_flag(Flags::CarryFlag);
    }
}

void HALT_0x76(Instruction* instruction)
{
    instruction->cpu->set_wait_for_interrupt(true);
}

void ADC_0x8F(Instruction* instruction)
{
    auto target = instruction->opcode & 0xF;
    auto number = 0;

    if (target == 14)
    {
        auto memoryFlag = (instruction->opcode & 0b01000000) == 0;

        if (memoryFlag)
        {
            ADD(RegisterType::None, true, instruction->cpu, false);
        }
        else
        {
            number = instruction->cpu->read_u8();
            ADD(number, true, instruction->cpu, true);
        }

        return;
    }

    RegisterType reg = RegisterType::None;

    switch (target)
    {
        case 8:
           reg = RegisterType::B;
           break;

        case 9:
           reg = RegisterType::C;
           break;

        case 10:
           reg = RegisterType::D;
           break;

        case 11:
           reg = RegisterType::E;
           break;

        case 12:
           reg = RegisterType::H;
           break;

        case 13:
           reg = RegisterType::L;
           break;

        case 15:
           reg = RegisterType::A;
           break;
    }

    ADD(reg, true, instruction->cpu, false);
}

void SUB_0x96(Instruction* instruction)
{
    SUB(RegisterType::None, false, instruction->cpu, false);
}

void SBC_0xDE(Instruction* instruction)
{
    auto target = instruction->opcode & 0xF;
    long number = 0;

    if (target == 14)
    {
        auto memoryFlag = (instruction->opcode & 0b01000000) == 0;

        if (memoryFlag)
        {
            SUB(RegisterType::None, true, instruction->cpu, false);
        }
        else
        {
            number = instruction->cpu->read_u8();
            SUB(number, true, instruction->cpu, true);
        }

        return;
    }
    
    RegisterType reg = RegisterType::None;

    switch (target)
    {
        case 8:
           reg = RegisterType::B;
           break;

        case 9:
           reg = RegisterType::C;
           break;

        case 10:
           reg = RegisterType::D;
           break;

        case 11:
           reg = RegisterType::E;
           break;

        case 12:
           reg = RegisterType::H;
           break;

        case 13:
           reg = RegisterType::L;
           break;

        case 15:
           reg = RegisterType::A;
           break;
    }

    SUB(reg, true, instruction->cpu, false);
}

void AND_0xA6(Instruction* instruction)
{
    auto val = instruction->cpu->get_memory()->read8(instruction->cpu->get(RegisterType::HL));
    auto result = instruction->cpu->get(RegisterType::A) & val;

    instruction->cpu->clear_flags();
    instruction->cpu->set(RegisterType::A, result);

    toggle_zero_flag(instruction->cpu, result);

    instruction->cpu->enable_flag(Flags::HalfCarryFlag);
}

void XOR_0xAE(Instruction* instruction)
{
    auto val = instruction->cpu->get_memory()->read8(instruction->cpu->get(RegisterType::HL));
    auto result = instruction->cpu->get(RegisterType::A) ^ val;

    instruction->cpu->clear_flags();
    instruction->cpu->set(RegisterType::A, result);

    toggle_zero_flag(instruction->cpu, result);
}

void OR_0xB6(Instruction* instruction)
{
    auto val = instruction->cpu->get_memory()->read8(instruction->cpu->get(RegisterType::HL));
    auto result = instruction->cpu->get(RegisterType::A) | val;

    instruction->cpu->clear_flags();
    instruction->cpu->set(RegisterType::A, result);

    toggle_zero_flag(instruction->cpu, result);
}

void CP_0xBB(Instruction* instruction)
{
    auto reg = instruction->cpu->read_byte_register_type(instruction->opcode);

    CP(instruction->cpu->get(reg), instruction->cpu);
}

void CALL_0xC4(Instruction* instruction)
{
    auto addr = instruction->cpu->read_u16();
    bool check = false;

    switch ((instruction->opcode >> 3) & 0x03)
    {
        case 0x00:
            check = !instruction->cpu->is_flag_set(Flags::ZeroFlag);
            break;

        case 0x01:
            check = instruction->cpu->is_flag_set(Flags::ZeroFlag);
            break;

        case 0x02:
            check = !instruction->cpu->is_flag_set(Flags::CarryFlag);
            break;

        case 0x03:
            check = instruction->cpu->is_flag_set(Flags::CarryFlag);
            break;
    }

    if (check)
    {
        instruction->cpu->push_stack(instruction->cpu->get(RegisterType::PC));
        instruction->cpu->set(RegisterType::PC, addr);
        instruction->ticks += 12;
    }
}

void ADD_0xC6(Instruction* instruction)
{
    ADD(instruction->cpu->read_u8(), false, instruction->cpu, true);
}

void SUB_0xD6(Instruction* instruction)
{
    SUB(instruction->cpu->read_u8(), false, instruction->cpu, true);
}

void ADD_0xE8(Instruction* instruction)
{
    ADD_16(RegisterType::SP, instruction->cpu->read_s8(), instruction->cpu, true);
}

void XOR_0xEE(Instruction* instruction)
{
    auto val = instruction->cpu->read_u8();
    auto result = instruction->cpu->get(RegisterType::A) ^ val;

    instruction->cpu->clear_flags();
    instruction->cpu->set(RegisterType::A, result);

    toggle_zero_flag(instruction->cpu, result);
}

void LD_0xF2(Instruction* instruction)
{
    instruction->cpu->set(RegisterType::A, instruction->cpu->get_memory()->read8(0xFF00 + instruction->cpu->get(RegisterType::C)));
}

void OR_0xF6(Instruction* instruction)
{
    auto val = instruction->cpu->read_u8();
    auto result = instruction->cpu->get(RegisterType::A) | val;

    instruction->cpu->clear_flags();
    instruction->cpu->set(RegisterType::A, result);

    toggle_zero_flag(instruction->cpu, result);
}

void LD_0xF8(Instruction* instruction)
{
    instruction->cpu->clear_flags();

    auto SP = instruction->cpu->get(RegisterType::SP);
    auto val = instruction->cpu->read_s8();
    auto result = (SP + val) & 0xFFFF;

    if (((SP ^ val ^ result) & 0x100) == 0x100)
    {
        instruction->cpu->enable_flag(Flags::CarryFlag);
    }

    if (((SP ^ val ^ result) & 0x10) == 0x10)
    {
        instruction->cpu->enable_flag(Flags::HalfCarryFlag);
    }
    
    instruction->cpu->set(RegisterType::HL, result);
}

void LD_0xF9(Instruction* instruction)
{
    instruction->cpu->set(RegisterType::SP, instruction->cpu->get(RegisterType::HL));
}

void SRL_0x38(Instruction* instruction)
{
    instruction->cpu->cycle(4);

    auto reg = instruction->cpu->read_byte_register_type(instruction->opcode);

    if ((instruction->opcode & 0x7) == 6)
    {
        SRL(RegisterType::None, instruction->cpu);
    }
    else
    {
        SRL(reg, instruction->cpu);
    }
}

void RLC_0x00(Instruction* instruction)
{
    instruction->cpu->cycle(4);

    auto reg = instruction->cpu->read_byte_register_type(instruction->opcode);
    long value = 0;

    instruction->cpu->disable_flag(Flags::HalfCarryFlag);
    instruction->cpu->disable_flag(Flags::AddSubFlag);

    if ((instruction->opcode & 0x7) == 6)
    {
        value = instruction->cpu->get_memory()->read8(instruction->cpu->get(RegisterType::HL));

        instruction->cpu->cycle(4);
    }
    else
    {
        value = instruction->cpu->get(reg);
    }

    if (value > 0x7F)
    {
        instruction->cpu->enable_flag(Flags::CarryFlag);
    }
    else
    {
        instruction->cpu->disable_flag(Flags::CarryFlag);
    }

    auto carry = instruction->cpu->is_flag_set(Flags::CarryFlag) ? 1 : 0;
    auto result = ((value << 1) & 0xFF) | (carry);

    if ((instruction->opcode & 0x7) == 6)
    {
        instruction->cpu->get_memory()->write8(instruction->cpu->get(RegisterType::HL), result);

        instruction->cpu->cycle(4);
    }
    else
    {
        instruction->cpu->set(reg, result);
    }

    toggle_zero_flag(instruction->cpu, result);
    instruction->cpu->cycle(4);
}

void RRC_0x08(Instruction* instruction)
{
    instruction->cpu->cycle(4);

    auto reg = instruction->cpu->read_byte_register_type(instruction->opcode);
    long result = 0;

    instruction->cpu->clear_flags();

    if ((instruction->opcode & 0x7) == 6)
    {
        result = instruction->cpu->get_memory()->read8(instruction->cpu->get(RegisterType::HL));

        instruction->cpu->cycle(4);
    }
    else
    {
        result = instruction->cpu->get(reg);
    }

    if ((result & 0x01) != 0)
    {
        instruction->cpu->enable_flag(Flags::CarryFlag);

        result >>= 1;
        result |= 0x80;
    }
    else
    {
        result >>= 1;
    }

    if ((instruction->opcode & 0x7) == 6)
    {
        instruction->cpu->get_memory()->write8(instruction->cpu->get(RegisterType::HL), result);

        instruction->cpu->cycle(4);
    }
    else
    {
        instruction->cpu->set(reg, result);
    }

    toggle_zero_flag(instruction->cpu, result);
    instruction->cpu->cycle(4);
}

void RR_0x19(Instruction* instruction)
{
    instruction->cpu->cycle(4);

    auto reg = instruction->cpu->read_byte_register_type(instruction->opcode);
    long result = 0;

    if ((instruction->opcode & 0x7) == 6)
    {
        result = instruction->cpu->get_memory()->read8(instruction->cpu->get(RegisterType::HL));

        instruction->cpu->cycle(4);
    }
    else
    {
        result = instruction->cpu->get(reg);
    }

    auto carry = instruction->cpu->is_flag_set(Flags::CarryFlag) ? 0x80 : 0;

    instruction->cpu->clear_flags();

    if ((result & 0x01) != 0)
    {
        instruction->cpu->enable_flag(Flags::CarryFlag);
    }

    result >>= 1;
    result |= carry;

    if ((instruction->opcode & 0x7) == 6)
    {
        instruction->cpu->get_memory()->write8(instruction->cpu->get(RegisterType::HL), result);

        instruction->cpu->cycle(4);
    }
    else
    {
        instruction->cpu->set(reg, result);
    }

    toggle_zero_flag(instruction->cpu, result);
    instruction->cpu->cycle(4);
}

void SLA_0x20(Instruction* instruction)
{
    instruction->cpu->cycle(4);

    auto reg = instruction->cpu->read_byte_register_type(instruction->opcode);
    long value = 0;

    if ((instruction->opcode & 0x7) == 6)
    {
        value = instruction->cpu->get_memory()->read8(instruction->cpu->get(RegisterType::HL));

        instruction->cpu->cycle(4);
    }
    else
    {
        value = instruction->cpu->get(reg);
    }

    instruction->cpu->disable_flag(Flags::HalfCarryFlag);
    instruction->cpu->disable_flag(Flags::AddSubFlag);

    if (value > 0x7F)
    {
        instruction->cpu->enable_flag(Flags::CarryFlag);
    }
    else
    {
        instruction->cpu->disable_flag(Flags::CarryFlag);
    }
    
    auto result = (value << 1) & 0xFF;

    if ((instruction->opcode & 0x7) == 6)
    {
        instruction->cpu->get_memory()->write8(instruction->cpu->get(RegisterType::HL), result);

        instruction->cpu->cycle(4);
    }
    else
    {
        instruction->cpu->set(reg, result);
    }

    toggle_zero_flag(instruction->cpu, result);
    instruction->cpu->cycle(4);
}

void SRA_0x28(Instruction* instruction)
{
    instruction->cpu->cycle(4);

    auto reg = instruction->cpu->read_byte_register_type(instruction->opcode);
    long result = 0;

    if ((instruction->opcode & 0x7) == 6) {
        result = instruction->cpu->get_memory()->read8(instruction->cpu->get(RegisterType::HL));

        instruction->cpu->cycle(4);
    } else {
        result = instruction->cpu->get(reg);
    }

    instruction->cpu->clear_flags();

    if ((result & 0x01) != 0) {
        instruction->cpu->enable_flag(Flags::CarryFlag);
    }

    if ((result & 0x80) != 0) {
        result >>= 1;
        result |= 0x80;
    } else {
        result >>= 1;
    }

    if ((instruction->opcode & 0x7) == 6) {
        instruction->cpu->get_memory()->write8(instruction->cpu->get(RegisterType::HL), result);

        instruction->cpu->cycle(4);
    } else {
        instruction->cpu->set(reg, result);
    }

    toggle_zero_flag(instruction->cpu, result);
    instruction->cpu->cycle(4);
}

void SET_0xC0(Instruction* instruction)
{
    instruction->cpu->cycle(4);

    auto reg = instruction->cpu->read_byte_register_type(instruction->opcode);
    auto bit = (instruction->opcode & 0b00111000) >> 3;

    long result = 0;
    if ((instruction->opcode & 0x7) == 6) {
        result = instruction->cpu->get_memory()->read8(instruction->cpu->get(RegisterType::HL));

        instruction->cpu->cycle(4);
    } else {
        result = instruction->cpu->get(reg);
    }

    result |= (1 << bit);

    if ((instruction->opcode & 0x7) == 6) {
        instruction->cpu->get_memory()->write8(instruction->cpu->get(RegisterType::HL), result);

        instruction->cpu->cycle(4);
    } else {
        instruction->cpu->set(reg, result);
    }

    instruction->cpu->cycle(4);
}