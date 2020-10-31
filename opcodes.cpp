#include "opcodes.h"
#include "gameboy_cpu.h"
#include "memory.h"

void toggle_zero_flag(GameboyCPU* cpu, long result)
{
    cpu->set_flag(Flags::ZeroFlag, (result & 0xFF) == 0);
}

void BIT_Impl(long reg, long bit, GameboyCPU* cpu)
{
    long value = 0;
    
    switch (reg)
    {
        case RegisterType::B:
            value = cpu->registers.B;
            break;

        case RegisterType::C:
            value = cpu->registers.C;
            break;

        case RegisterType::D:
            value = cpu->registers.D;
            break;

        case RegisterType::E:
            value = cpu->registers.E;
            break;

        case RegisterType::H:
            value = cpu->registers.H;
            break;

        case RegisterType::L:
            value = cpu->registers.L;
            break;

        case RegisterType::HL:
            value = cpu->memory.read8(cpu->registers.HL);
            cpu->tick(4);
            break;

        case RegisterType::A:
            value = cpu->registers.A;
            break;
    }

    toggle_zero_flag(cpu, ((value >> bit) & 0x01));

    cpu->enable_flag(Flags::HalfCarryFlag);
    cpu->disable_flag(Flags::AddSubFlag);

    cpu->tick(4);
}

void CP(long val, GameboyCPU* cpu)
{
    cpu->clear_flags();

    long A = cpu->registers.A;

    cpu->enable_flag(Flags::AddSubFlag);
    cpu->set_flag(Flags::ZeroFlag, val == A);
    cpu->set_flag(Flags::CarryFlag, (A - val) < 0);
    cpu->set_flag(Flags::HalfCarryFlag, ((A - val) & 0xF) > (A & 0xF));
}

void SUB(long reg, bool use_carry, GameboyCPU* cpu, bool is_number)
{
    long value = 0;

    cpu->enable_flag(Flags::AddSubFlag);

    if (is_number)
    {
        value = reg;
    }
    else
    {
        switch (reg)
        {
            case RegisterType::B:
                value = cpu->registers.B;
                break;

            case RegisterType::C:
                value = cpu->registers.C;
                break;

            case RegisterType::D:
                value = cpu->registers.D;
                break;

            case RegisterType::E:
                value = cpu->registers.E;
                break;

            case RegisterType::H:
                value = cpu->registers.H;
                break;

            case RegisterType::L:
                value = cpu->registers.L;
                break;

            case RegisterType::HL:
                value = cpu->memory.read8(cpu->registers.HL);
                break;

            case RegisterType::A:
                value = cpu->registers.A;
                break;
        }
    }

    long A = cpu->registers.A;
    long extra = (use_carry && cpu->is_flag_set(Flags::CarryFlag)) ? 1 : 0;
    long result = A - value - extra;

    if (result < 0)
    {
        cpu->enable_flag(Flags::CarryFlag);
    }
    else
    {
        cpu->disable_flag(Flags::CarryFlag);
    }

    if ((A & 0xF) - (value & 0xF) - extra < 0) {
        cpu->enable_flag(Flags::HalfCarryFlag);
    } else {
        cpu->disable_flag(Flags::HalfCarryFlag);
    }

    cpu->registers.A = result;

    toggle_zero_flag(cpu, result);
}

void ADD(long reg, bool add_carry, GameboyCPU* cpu, bool is_number)
{
    long value = 0;

    if (is_number)
    {
        value = reg;
    }
    else
    {
        switch (reg)
        {
            case RegisterType::B:
                value = cpu->registers.B;
                break;

            case RegisterType::C:
                value = cpu->registers.C;
                break;

            case RegisterType::D:
                value = cpu->registers.D;
                break;

            case RegisterType::E:
                value = cpu->registers.E;
                break;

            case RegisterType::H:
                value = cpu->registers.H;
                break;

            case RegisterType::L:
                value = cpu->registers.L;
                break;

            case RegisterType::HL:
                value = cpu->memory.read8(cpu->registers.HL);
                break;

            case RegisterType::A:
                value = cpu->registers.A;
                break;
        }
    }

    long A = cpu->registers.A;
    long extra = (add_carry && cpu->is_flag_set(Flags::CarryFlag)) ? 1 : 0;
    long result = A + value + extra;

    if (result > 0xFF)
    {
        cpu->enable_flag(Flags::CarryFlag);
    }
    else
    {
        cpu->disable_flag(Flags::CarryFlag);
    }

    if ((A & 0xF) + (value & 0xF) + extra > 0xF) {
        cpu->enable_flag(Flags::HalfCarryFlag);
    } else {
        cpu->disable_flag(Flags::HalfCarryFlag);
    }

    cpu->registers.A = result;
    toggle_zero_flag(cpu, result);

    cpu->disable_flag(Flags::AddSubFlag);
}

void SWAP(long reg, GameboyCPU* cpu)
{
    cpu->clear_flags();

    long value = 0;

    switch (reg)
    {
        case RegisterType::B:
            value = cpu->registers.B;
            break;

        case RegisterType::C:
            value = cpu->registers.C;
            break;

        case RegisterType::D:
            value = cpu->registers.D;
            break;

        case RegisterType::E:
            value = cpu->registers.E;
            break;

        case RegisterType::H:
            value = cpu->registers.H;
            break;

        case RegisterType::L:
            value = cpu->registers.L;
            break;

        case RegisterType::HL:
            value = cpu->memory.read8(cpu->registers.HL);
            cpu->tick(4);
            break;

        case RegisterType::A:
            value = cpu->registers.A;
            break;
    }

    long result = ((value & 0x0F) << 4) | ((value & 0xF0) >> 4);

    switch (reg)
    {
        case RegisterType::B:
            cpu->registers.B = result;
            break;

        case RegisterType::C:
            cpu->registers.C = result;
            break;

        case RegisterType::D:
            cpu->registers.D = result;
            break;

        case RegisterType::E:
            cpu->registers.E = result;
            break;

        case RegisterType::H:
            cpu->registers.H = result;
            break;

        case RegisterType::L:
            cpu->registers.L = result;
            break;

        case RegisterType::HL:
            cpu->memory.write8(cpu->registers.HL, result);
            cpu->tick(4);
            break;

        case RegisterType::A:
            cpu->registers.A = result;
            break;
    }

    toggle_zero_flag(cpu, result);
    cpu->tick(4);
}

void SRL(long reg, GameboyCPU* cpu)
{
    cpu->clear_flags();

    long value = 0;

    switch (reg)
    {
        case RegisterType::B:
            value = cpu->registers.B;
            break;

        case RegisterType::C:
            value = cpu->registers.C;
            break;

        case RegisterType::D:
            value = cpu->registers.D;
            break;

        case RegisterType::E:
            value = cpu->registers.E;
            break;

        case RegisterType::H:
            value = cpu->registers.H;
            break;

        case RegisterType::L:
            value = cpu->registers.L;
            break;

        case RegisterType::HL:
            value = cpu->memory.read8(cpu->registers.HL);
            cpu->tick(4);
            break;

        case RegisterType::A:
            value = cpu->registers.A;
            break;
    }

    if ((value & 0x01) != 0) {
        cpu->enable_flag(Flags::CarryFlag);
    }

    value >>= 1;

    switch (reg)
    {
        case RegisterType::B:
            cpu->registers.B = value;
            break;

        case RegisterType::C:
            cpu->registers.C = value;
            break;

        case RegisterType::D:
            cpu->registers.D = value;
            break;

        case RegisterType::E:
            cpu->registers.E = value;
            break;

        case RegisterType::H:
            cpu->registers.H = value;
            break;

        case RegisterType::L:
            cpu->registers.L = value;
            break;

        case RegisterType::HL:
            cpu->memory.write8(cpu->registers.HL, value);
            cpu->tick(4);
            break;

        case RegisterType::A:
            cpu->registers.A = value;
            break;
    }
    
    toggle_zero_flag(cpu, value);

    cpu->tick(4);
}

void LD_0x01(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.BC = cpu->read_u16();
}

void LD_0x11(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.DE = cpu->read_u16();
}

void LD_0x21(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.HL = cpu->read_u16();
}

void LD_0x31(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.SP = cpu->read_u16();
}

void XOR_0xA8(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    long result = cpu->registers.A ^ cpu->registers.B;

    cpu->clear_flags();
    cpu->registers.A = result;

    toggle_zero_flag(cpu, result);
}

void XOR_0xA9(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    long result = cpu->registers.A ^ cpu->registers.C;

    cpu->clear_flags();
    cpu->registers.A = result;

    toggle_zero_flag(cpu, result);
}

void XOR_0xAA(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    long result = cpu->registers.A ^ cpu->registers.D;

    cpu->clear_flags();
    cpu->registers.A = result;

    toggle_zero_flag(cpu, result);
}

void XOR_0xAB(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    long result = cpu->registers.A ^ cpu->registers.E;

    cpu->clear_flags();
    cpu->registers.A = result;

    toggle_zero_flag(cpu, result);
}

void XOR_0xAC(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    long result = cpu->registers.A ^ cpu->registers.H;

    cpu->clear_flags();
    cpu->registers.A = result;

    toggle_zero_flag(cpu, result);
}

void XOR_0xAD(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    long result = cpu->registers.A ^ cpu->registers.L;

    cpu->clear_flags();
    cpu->registers.A = result;

    toggle_zero_flag(cpu, result);
}

void XOR_0xAF(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    long result = cpu->registers.A ^ cpu->registers.A;

    cpu->clear_flags();
    cpu->registers.A = result;

    toggle_zero_flag(cpu, result);
}

void LD_0x32(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->memory.write8(cpu->registers.HL, cpu->registers.A);
    cpu->registers.HL--;
}

void JR_0x20(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    long relative = cpu->read_s8();
    bool check = false;

    switch ((opcode >> 3) & 0x03)
    {
        case 0x00:
            check = !cpu->is_flag_set(Flags::ZeroFlag);
            break;

        case 0x01:
            check = cpu->is_flag_set(Flags::ZeroFlag);
            break;

        case 0x02:
            check = !cpu->is_flag_set(Flags::CarryFlag);
            break;

        case 0x03:
            check = cpu->is_flag_set(Flags::CarryFlag);
            break;
    }

    if (check)
    {
        cpu->registers.PC += relative;
        instruction->ticks += 4;
    }
}

void LD_0x06(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.B = cpu->read_u8();
}

void LD_0x0E(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.C = cpu->read_u8();
}

void LD_0x16(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.D = cpu->read_u8();
}

void LD_0x1E(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.E = cpu->read_u8();
}

void LD_0x26(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.H = cpu->read_u8();
}

void LD_0x2E(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.L = cpu->read_u8();
}

void LD_0x3E(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.A = cpu->read_u8();
}

void LD_0xE2(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->memory.write8(0xFF00 + cpu->registers.C, cpu->registers.A);
}

void LD_0x70(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->memory.write8(cpu->registers.HL, cpu->registers.B);
}

void LD_0x71(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->memory.write8(cpu->registers.HL, cpu->registers.C);
}

void LD_0x72(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->memory.write8(cpu->registers.HL, cpu->registers.D);
}

void LD_0x73(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->memory.write8(cpu->registers.HL, cpu->registers.E);
}

void LD_0x74(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->memory.write8(cpu->registers.HL, cpu->registers.H);
}

void LD_0x75(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->memory.write8(cpu->registers.HL, cpu->registers.L);
}

void LD_0x77(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->memory.write8(cpu->registers.HL, cpu->registers.A);
}

void INC_0x04(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->disable_flag(Flags::ZeroFlag);
    cpu->disable_flag(Flags::AddSubFlag);

    long val = ++cpu->registers.B;

    if ((val & 0x0F) == 0x00)
    {
        cpu->enable_flag(Flags::HalfCarryFlag);
    }
    else
    {
        cpu->disable_flag(Flags::HalfCarryFlag);
    }

    toggle_zero_flag(cpu, val);
}

void INC_0x0C(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->disable_flag(Flags::ZeroFlag);
    cpu->disable_flag(Flags::AddSubFlag);

    long val = ++cpu->registers.C;

    if ((val & 0x0F) == 0x00)
    {
        cpu->enable_flag(Flags::HalfCarryFlag);
    }
    else
    {
        cpu->disable_flag(Flags::HalfCarryFlag);
    }

    toggle_zero_flag(cpu, val);
}

void INC_0x14(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->disable_flag(Flags::ZeroFlag);
    cpu->disable_flag(Flags::AddSubFlag);

    long val = ++cpu->registers.D;

    if ((val & 0x0F) == 0x00)
    {
        cpu->enable_flag(Flags::HalfCarryFlag);
    }
    else
    {
        cpu->disable_flag(Flags::HalfCarryFlag);
    }

    toggle_zero_flag(cpu, val);
}

void INC_0x1C(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->disable_flag(Flags::ZeroFlag);
    cpu->disable_flag(Flags::AddSubFlag);

    long val = ++cpu->registers.E;

    if ((val & 0x0F) == 0x00)
    {
        cpu->enable_flag(Flags::HalfCarryFlag);
    }
    else
    {
        cpu->disable_flag(Flags::HalfCarryFlag);
    }

    toggle_zero_flag(cpu, val);
}

void INC_0x24(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->disable_flag(Flags::ZeroFlag);
    cpu->disable_flag(Flags::AddSubFlag);

    long val = ++cpu->registers.H;

    if ((val & 0x0F) == 0x00)
    {
        cpu->enable_flag(Flags::HalfCarryFlag);
    }
    else
    {
        cpu->disable_flag(Flags::HalfCarryFlag);
    }

    toggle_zero_flag(cpu, val);
}

void INC_0x2C(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->disable_flag(Flags::ZeroFlag);
    cpu->disable_flag(Flags::AddSubFlag);

    long val = ++cpu->registers.L;

    if ((val & 0x0F) == 0x00)
    {
        cpu->enable_flag(Flags::HalfCarryFlag);
    }
    else
    {
        cpu->disable_flag(Flags::HalfCarryFlag);
    }

    toggle_zero_flag(cpu, val);
}

void INC_0x3C(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->disable_flag(Flags::ZeroFlag);
    cpu->disable_flag(Flags::AddSubFlag);

    long val = ++cpu->registers.A;

    if ((val & 0x0F) == 0x00)
    {
        cpu->enable_flag(Flags::HalfCarryFlag);
    }
    else
    {
        cpu->disable_flag(Flags::HalfCarryFlag);
    }

    toggle_zero_flag(cpu, val);
}

void LDH_0xE0(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->tick(4);

    long pos = 0xFF00 + cpu->read_u8();

    cpu->memory.write8(pos, cpu->registers.A);

    cpu->tick(4);
    cpu->tick(4);
}

void LD_0x1A(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.A = cpu->memory.read8(cpu->registers.DE);
}

void CALL_0xCD(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    long addr = cpu->read_u16();

    cpu->push_stack(cpu->registers.PC);
    cpu->registers.PC = addr;
}

void LD_0x40(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.B = cpu->registers.B;
}

void LD_0x41(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.B = cpu->registers.C;
}

void LD_0x42(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.B = cpu->registers.D;
}

void LD_0x43(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.B = cpu->registers.E;
}

void LD_0x44(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.B = cpu->registers.H;
}

void LD_0x45(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.B = cpu->registers.L;
}

void LD_0x47(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.B = cpu->registers.A;
}

void LD_0x48(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.C = cpu->registers.B;
}

void LD_0x49(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.C = cpu->registers.C;
}

void LD_0x4A(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.C = cpu->registers.D;
}

void LD_0x4B(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.C = cpu->registers.E;
}

void LD_0x4C(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.C = cpu->registers.H;
}

void LD_0x4D(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.C = cpu->registers.L;
}

void LD_0x4F(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.C = cpu->registers.A;
}

void LD_0x50(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.D = cpu->registers.B;
}

void LD_0x51(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.D = cpu->registers.C;
}

void LD_0x52(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.D = cpu->registers.D;
}

void LD_0x53(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.D = cpu->registers.E;
}

void LD_0x54(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.D = cpu->registers.H;
}

void LD_0x55(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.D = cpu->registers.L;
}

void LD_0x57(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.D = cpu->registers.A;
}

void LD_0x58(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.E = cpu->registers.B;
}

void LD_0x59(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.E = cpu->registers.C;
}

void LD_0x5A(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.E = cpu->registers.D;
}

void LD_0x5B(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.E = cpu->registers.E;
}

void LD_0x5C(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.E = cpu->registers.H;
}

void LD_0x5D(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.E = cpu->registers.L;
}

void LD_0x5F(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.E = cpu->registers.A;
}

void LD_0x60(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.H = cpu->registers.B;
}

void LD_0x61(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.H = cpu->registers.C;
}

void LD_0x62(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.H = cpu->registers.D;
}

void LD_0x63(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.H = cpu->registers.E;
}

void LD_0x64(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.H = cpu->registers.H;
}

void LD_0x65(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.H = cpu->registers.L;
}

void LD_0x67(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.H = cpu->registers.A;
}

void LD_0x68(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.L = cpu->registers.B;
}

void LD_0x69(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.L = cpu->registers.C;
}

void LD_0x6A(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.L = cpu->registers.D;
}

void LD_0x6B(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.L = cpu->registers.E;
}

void LD_0x6C(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.L = cpu->registers.H;
}

void LD_0x6D(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.L = cpu->registers.L;
}

void LD_0x6F(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.L = cpu->registers.A;
}

void LD_0x78(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.A = cpu->registers.B;
}

void LD_0x79(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.A = cpu->registers.C;
}

void LD_0x7A(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.A = cpu->registers.D;
}

void LD_0x7B(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.A = cpu->registers.E;
}

void LD_0x7C(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.A = cpu->registers.H;
}

void LD_0x7D(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.A = cpu->registers.L;
}

void LD_0x7F(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.A = cpu->registers.A;
}

void PUSH_0xC5(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->push_stack(cpu->registers.BC);
}

void PUSH_0xD5(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->push_stack(cpu->registers.DE);
}

void PUSH_0xE5(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->push_stack(cpu->registers.HL);
}

void PUSH_0xF5(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->push_stack(cpu->registers.AF);
}

void POP_0xC1(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.BC = cpu->pop_stack();
}

void POP_0xD1(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.DE = cpu->pop_stack();
}

void POP_0xE1(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.HL = cpu->pop_stack();
}

void POP_0xF1(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.AF = cpu->pop_stack() & 0xFFF0;
}

void DEC_0x05(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->enable_flag(Flags::AddSubFlag);
    cpu->disable_flag(Flags::ZeroFlag);

    long result = --cpu->registers.B;

    if ((result & 0x0F) == 0x0F) {
        cpu->enable_flag(Flags::HalfCarryFlag);
    } else {
        cpu->disable_flag(Flags::HalfCarryFlag);
    }

    toggle_zero_flag(cpu, result);
}

void DEC_0x0D(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->enable_flag(Flags::AddSubFlag);
    cpu->disable_flag(Flags::ZeroFlag);

    long result = --cpu->registers.C;

    if ((result & 0x0F) == 0x0F) {
        cpu->enable_flag(Flags::HalfCarryFlag);
    } else {
        cpu->disable_flag(Flags::HalfCarryFlag);
    }

    toggle_zero_flag(cpu, result);
}

void DEC_0x15(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->enable_flag(Flags::AddSubFlag);
    cpu->disable_flag(Flags::ZeroFlag);

    long result = --cpu->registers.D;

    if ((result & 0x0F) == 0x0F) {
        cpu->enable_flag(Flags::HalfCarryFlag);
    } else {
        cpu->disable_flag(Flags::HalfCarryFlag);
    }

    toggle_zero_flag(cpu, result);
}

void DEC_0x1D(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->enable_flag(Flags::AddSubFlag);
    cpu->disable_flag(Flags::ZeroFlag);

    long result = --cpu->registers.E;

    if ((result & 0x0F) == 0x0F) {
        cpu->enable_flag(Flags::HalfCarryFlag);
    } else {
        cpu->disable_flag(Flags::HalfCarryFlag);
    }

    toggle_zero_flag(cpu, result);
}

void DEC_0x25(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->enable_flag(Flags::AddSubFlag);
    cpu->disable_flag(Flags::ZeroFlag);

    long result = --cpu->registers.H;

    if ((result & 0x0F) == 0x0F) {
        cpu->enable_flag(Flags::HalfCarryFlag);
    } else {
        cpu->disable_flag(Flags::HalfCarryFlag);
    }

    toggle_zero_flag(cpu, result);
}

void DEC_0x2D(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->enable_flag(Flags::AddSubFlag);
    cpu->disable_flag(Flags::ZeroFlag);

    long result = --cpu->registers.L;

    if ((result & 0x0F) == 0x0F) {
        cpu->enable_flag(Flags::HalfCarryFlag);
    } else {
        cpu->disable_flag(Flags::HalfCarryFlag);
    }

    toggle_zero_flag(cpu, result);
}

void DEC_0x3D(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->enable_flag(Flags::AddSubFlag);
    cpu->disable_flag(Flags::ZeroFlag);

    long result = --cpu->registers.A;

    if ((result & 0x0F) == 0x0F) {
        cpu->enable_flag(Flags::HalfCarryFlag);
    } else {
        cpu->disable_flag(Flags::HalfCarryFlag);
    }

    toggle_zero_flag(cpu, result);
}

void LD_0x22(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->memory.write8(cpu->registers.HL, cpu->registers.A);
    cpu->registers.HL++;
}

void INC_0x03(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.BC++;
}

void INC_0x13(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.DE++;
}

void INC_0x23(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.HL++;
}

void INC_0x33(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.SP++;
}

void RET_0xC9(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.PC = cpu->pop_stack();
}

void CP_0xFE(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    CP(cpu->read_u8(), cpu);
}

void LD_0xEA(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->tick(4);
    cpu->tick(4);

    long addr = cpu->read_u16();

    cpu->memory.write8(addr, cpu->registers.A);

    cpu->tick(4);
    cpu->tick(4);
}

void LDH_0xF0(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->tick(4);

    long pos = 0xFF00 + cpu->read_u8();

    cpu->registers.A = cpu->memory.read8(pos);

    cpu->tick(4);
    cpu->tick(4);
}

void SUB_0x90(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    SUB(cpu->read_byte_register_type(opcode), false, cpu, false);
}

void JR_0x18(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    long relative = cpu->read_s8();

    cpu->registers.PC += relative;
}

void CP_0xBE(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    CP(cpu->memory.read8(cpu->registers.HL), cpu);
}

void ADD_0x86(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    ADD(RegisterType::HL, false, cpu, false);
}

void RL_0x11(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->tick(4);

    long reg = cpu->read_byte_register_type(opcode, true);
    long result = 0;

    switch (reg)
    {
        case RegisterType::B:
            result = cpu->registers.B;
            break;

        case RegisterType::C:
            result = cpu->registers.C;
            break;

        case RegisterType::D:
            result = cpu->registers.D;
            break;

        case RegisterType::E:
            result = cpu->registers.E;
            break;

        case RegisterType::H:
            result = cpu->registers.H;
            break;

        case RegisterType::L:
            result = cpu->registers.L;
            break;

        case RegisterType::A:
            result = cpu->registers.A;
            break;
        
        case RegisterType::HL:
            result = cpu->memory.read8(cpu->registers.HL);
            cpu->tick(4);
            break;
    }

    long carry = cpu->is_flag_set(Flags::CarryFlag) ? 0x01 : 0x00;

    cpu->clear_flags();

    if ((result & 0x80) != 0) {
        cpu->enable_flag(Flags::CarryFlag);
    }

    result <<= 1;
    result |= carry;

    switch (reg)
    {
        case RegisterType::B:
            cpu->registers.B = result;
            break;

        case RegisterType::C:
            cpu->registers.C = result;
            break;

        case RegisterType::D:
            cpu->registers.D = result;
            break;

        case RegisterType::E:
            cpu->registers.E = result;
            break;

        case RegisterType::H:
            cpu->registers.H = result;
            break;

        case RegisterType::L:
            cpu->registers.L = result;
            break;

        case RegisterType::A:
            cpu->registers.A = result;
            break;
        
        case RegisterType::HL:
            cpu->memory.write8(cpu->registers.HL, result);
            cpu->tick(4);
            break;
    }

    toggle_zero_flag(cpu, result);
    cpu->tick(4);
}

void RLA_0x17(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    long carry = cpu->is_flag_set(Flags::CarryFlag) ? 1 : 0;
    long result = cpu->registers.A;

    cpu->clear_flags();

    if ((result & 0x80) != 0) {
        cpu->enable_flag(Flags::CarryFlag);
    }

    result <<= 1;
    result |= carry;

    cpu->registers.A = result;
}

void BIT_0x7C(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->tick(4);

    long reg = cpu->read_byte_register_type(opcode, true);
    long bit = (opcode & 0b00111000) >> 3;

    BIT_Impl(reg, bit, cpu);
}

void JP_0xC3(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    long addr = cpu->read_u16();
    cpu->registers.PC = addr;
}

void DI_0xF3(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->set_enable_interrupts(false);
}

void LD_0x36(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->tick(4);

    long val = cpu->read_u8();

    cpu->memory.write8(cpu->registers.HL, val);

    cpu->tick(4);
    cpu->tick(4);
}

void LD_0x2A(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.A = cpu->memory.read8(cpu->registers.HL);
    cpu->registers.HL++;
}

void DEC_0x0B(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.BC--;
}

void DEC_0x1B(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.DE--;
}

void DEC_0x2B(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.HL--;
}

void DEC_0x3B(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.SP--;
}

void OR_0xB0(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    long result = cpu->registers.A | cpu->registers.B;

    cpu->clear_flags();
    cpu->registers.A = result;

    toggle_zero_flag(cpu, result);
}

void OR_0xB1(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    long result = cpu->registers.A | cpu->registers.C;

    cpu->clear_flags();
    cpu->registers.A = result;

    toggle_zero_flag(cpu, result);
}

void OR_0xB2(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    long result = cpu->registers.A | cpu->registers.D;

    cpu->clear_flags();
    cpu->registers.A = result;

    toggle_zero_flag(cpu, result);
}

void OR_0xB3(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    long result = cpu->registers.A | cpu->registers.E;

    cpu->clear_flags();
    cpu->registers.A = result;

    toggle_zero_flag(cpu, result);
}

void OR_0xB4(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    long result = cpu->registers.A | cpu->registers.H;

    cpu->clear_flags();
    cpu->registers.A = result;

    toggle_zero_flag(cpu, result);
}

void OR_0xB5(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    long result = cpu->registers.A | cpu->registers.L;

    cpu->clear_flags();
    cpu->registers.A = result;

    toggle_zero_flag(cpu, result);
}

void OR_0xB7(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    long result = cpu->registers.A | cpu->registers.A;

    cpu->clear_flags();
    cpu->registers.A = result;

    toggle_zero_flag(cpu, result);
}

void EI_0xFB(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->set_enable_interrupts(true);
}

void AND_0xA0(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    long reg = cpu->read_byte_register_type(opcode);
    long result = cpu->registers.A & cpu->registers.B;

    cpu->clear_flags();
    cpu->registers.A = result;

    toggle_zero_flag(cpu, result);

    cpu->enable_flag(Flags::HalfCarryFlag);
}

void AND_0xA1(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    long reg = cpu->read_byte_register_type(opcode);
    long result = cpu->registers.A & cpu->registers.C;

    cpu->clear_flags();
    cpu->registers.A = result;

    toggle_zero_flag(cpu, result);

    cpu->enable_flag(Flags::HalfCarryFlag);
}

void AND_0xA2(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    long reg = cpu->read_byte_register_type(opcode);
    long result = cpu->registers.A & cpu->registers.D;

    cpu->clear_flags();
    cpu->registers.A = result;

    toggle_zero_flag(cpu, result);

    cpu->enable_flag(Flags::HalfCarryFlag);
}

void AND_0xA3(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    long reg = cpu->read_byte_register_type(opcode);
    long result = cpu->registers.A & cpu->registers.E;

    cpu->clear_flags();
    cpu->registers.A = result;

    toggle_zero_flag(cpu, result);

    cpu->enable_flag(Flags::HalfCarryFlag);
}

void AND_0xA4(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    long reg = cpu->read_byte_register_type(opcode);
    long result = cpu->registers.A & cpu->registers.H;

    cpu->clear_flags();
    cpu->registers.A = result;

    toggle_zero_flag(cpu, result);

    cpu->enable_flag(Flags::HalfCarryFlag);
}

void AND_0xA5(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    long reg = cpu->read_byte_register_type(opcode);
    long result = cpu->registers.A & cpu->registers.L;

    cpu->clear_flags();
    cpu->registers.A = result;

    toggle_zero_flag(cpu, result);

    cpu->enable_flag(Flags::HalfCarryFlag);
}

void AND_0xA7(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    long reg = cpu->read_byte_register_type(opcode);
    long result = cpu->registers.A & cpu->registers.A;

    cpu->clear_flags();
    cpu->registers.A = result;

    toggle_zero_flag(cpu, result);

    cpu->enable_flag(Flags::HalfCarryFlag);
}

void RET_0xC0(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    bool check = false;

    switch ((opcode >> 3) & 0x03)
    {
        case 0x00:
            check = !cpu->is_flag_set(Flags::ZeroFlag);
            break;

        case 0x01:
            check = cpu->is_flag_set(Flags::ZeroFlag);
            break;

        case 0x02:
            check = !cpu->is_flag_set(Flags::CarryFlag);
            break;

        case 0x03:
            check = cpu->is_flag_set(Flags::CarryFlag);
            break;
    }

    if (check)
    {
        cpu->registers.PC = cpu->pop_stack();
        instruction->ticks += 12;
    }
}

void LD_0xFA(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->tick(4);
    cpu->tick(4);

    long addr = cpu->read_u16();
    cpu->registers.A = cpu->memory.read8(addr);

    cpu->tick(4);
    cpu->tick(4);
}

void INC_0x34(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->disable_flag(Flags::ZeroFlag);
    cpu->disable_flag(Flags::AddSubFlag);

    long HL = cpu->registers.HL;
    long val = (cpu->memory.read8(HL) + 1) & 0xFF;

    cpu->tick(4);

    toggle_zero_flag(cpu, val);

    if ((val & 0xF) == 0x00) {
        cpu->enable_flag(Flags::HalfCarryFlag);
    } else {
        cpu->disable_flag(Flags::HalfCarryFlag);
    }

    cpu->memory.write8(HL, val);

    cpu->tick(4);
    cpu->tick(4);
}

void RETI_0xD9(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.PC = cpu->pop_stack();
    cpu->set_enable_interrupts(true);
}

void CPL_0x2F(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.A = ((long)cpu->registers.A) ^ 0xFF;

    cpu->enable_flag(Flags::HalfCarryFlag);
    cpu->enable_flag(Flags::AddSubFlag);
}

void AND_0xE6(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    long val = cpu->read_u8();
    long result = cpu->registers.A & val;

    cpu->clear_flags();
    cpu->registers.A = result;

    toggle_zero_flag(cpu, result);

    cpu->enable_flag(Flags::HalfCarryFlag);
}

void SWAP_0x37(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->tick(4);

    long reg = cpu->read_byte_register_type(opcode, true);

    SWAP(reg, cpu);
}

void RST_0xEF(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    long t = ((opcode >> 3) & 0x07);
    long n = t * 0x08;

    cpu->push_stack(cpu->registers.PC);
    cpu->registers.PC = n;
}

void ADD_0x81(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    ADD(cpu->read_byte_register_type(opcode), false, cpu, false);
}

inline void ADD_IMPL(uint8_t opcode, GameboyCPU* cpu, long data)
{
    long reg = cpu->read_register_type(opcode >> 4, false);

    cpu->disable_flag(Flags::AddSubFlag);

    long HL = cpu->registers.HL;
    long result = (HL + data) & 0xFFFF;

    if (result < HL) {
        cpu->enable_flag(Flags::CarryFlag);
    } else {
        cpu->disable_flag(Flags::CarryFlag);
    }

    if ((result ^ HL ^ data) & 0x1000) {
        cpu->enable_flag(Flags::HalfCarryFlag);
    } else {
        cpu->disable_flag(Flags::HalfCarryFlag);
    }

    cpu->registers.HL = result;
}

void ADD_0x09(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    ADD_IMPL(opcode, cpu, cpu->registers.BC);
}

void ADD_0x19(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    ADD_IMPL(opcode, cpu, cpu->registers.DE);
}

void ADD_0x29(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    ADD_IMPL(opcode, cpu, cpu->registers.HL);
}

void ADD_0x39(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    ADD_IMPL(opcode, cpu, cpu->registers.SP);
}

void LD_0x46(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.B = cpu->memory.read8(cpu->registers.HL);
}

void LD_0x4E(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.C = cpu->memory.read8(cpu->registers.HL);
}

void LD_0x56(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.D = cpu->memory.read8(cpu->registers.HL);
}

void LD_0x5E(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.E = cpu->memory.read8(cpu->registers.HL);
}

void LD_0x66(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.H = cpu->memory.read8(cpu->registers.HL);
}

void LD_0x6E(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.L = cpu->memory.read8(cpu->registers.HL);
}

void LD_0x7E(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.A = cpu->memory.read8(cpu->registers.HL);
}

void JP_0xE9(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.PC = cpu->registers.HL;
}

void RES_0x87(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->tick(4);

    long reg = cpu->read_byte_register_type(opcode, true);
    long bit = (opcode & 0b00111000) >> 3;

    long result = 0;

    
    switch (reg)
    {
        case RegisterType::B:
            result = cpu->registers.B;
            break;

        case RegisterType::C:
            result = cpu->registers.C;
            break;

        case RegisterType::D:
            result = cpu->registers.D;
            break;

        case RegisterType::E:
            result = cpu->registers.E;
            break;

        case RegisterType::H:
            result = cpu->registers.H;
            break;

        case RegisterType::L:
            result = cpu->registers.L;
            break;

        case RegisterType::A:
            result = cpu->registers.A;
            break;
        
        case RegisterType::HL:
            result = cpu->memory.read8(cpu->registers.HL);
            cpu->tick(4);
            break;
    }

    result &= ~(1 << bit);

    switch (reg)
    {
        case RegisterType::B:
            cpu->registers.B = result;
            break;

        case RegisterType::C:
            cpu->registers.C = result;
            break;

        case RegisterType::D:
            cpu->registers.D = result;
            break;

        case RegisterType::E:
            cpu->registers.E = result;
            break;

        case RegisterType::H:
            cpu->registers.H = result;
            break;

        case RegisterType::L:
            cpu->registers.L = result;
            break;

        case RegisterType::A:
            cpu->registers.A = result;
            break;
        
        case RegisterType::HL:
            cpu->memory.write8(cpu->registers.HL, result);
            cpu->tick(4);
            break;
    }

    cpu->tick(4);
}

void LD_0x12(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->memory.write8(cpu->registers.DE, cpu->registers.A);
}

void JP_0xC2(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    long addr = cpu->read_u16();
    bool check = false;

    switch ((opcode >> 3) & 0x03)
    {
        case 0x00:
            check = !cpu->is_flag_set(Flags::ZeroFlag);
            break;

        case 0x01:
            check = cpu->is_flag_set(Flags::ZeroFlag);
            break;

        case 0x02:
            check = !cpu->is_flag_set(Flags::CarryFlag);
            break;

        case 0x03:
            check = cpu->is_flag_set(Flags::CarryFlag);
            break;
    }

    if (check)
    {
        cpu->registers.PC = addr;
        instruction->ticks += 4;
    }
}

void LD_0x02(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->memory.write8(cpu->registers.BC, cpu->registers.A);
}

void RLCA_0x07(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    long val = cpu->registers.A;
    cpu->clear_flags();

    if ((val & 0x80) != 0) {
        cpu->enable_flag(Flags::CarryFlag);

        val <<= 1;
        val |= 0x01;
    } else {
        val <<= 1;
    }

    cpu->registers.A = val;
}

void LD_0x08(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    long addr = cpu->read_u16();

    long SP = cpu->registers.SP;
    cpu->memory.write8(addr + 0, SP & 0xFF);
    cpu->memory.write8(addr + 1, (SP >> 8) & 0xFF);
}

void LD_0x0A(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    long val = cpu->memory.read8(cpu->registers.BC);

    cpu->registers.A = val;
}

void RRCA_0x0F(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    long val = cpu->registers.A;
    cpu->clear_flags();

    if ((val & 0x01) != 0) {
        cpu->enable_flag(Flags::CarryFlag);

        val >>= 1;
        val |= 0x80;
    } else {
        val >>= 1;
    }

    cpu->registers.A = val;
}

void RRA_0x1F(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    long carry = cpu->is_flag_set(Flags::CarryFlag) ? 0x80 : 0;
    long result = cpu->registers.A;

    cpu->clear_flags();

    if ((result & 0x01) != 0)
    {
        cpu->enable_flag(Flags::CarryFlag);
    }

    result >>= 1;
    result |= carry;

    cpu->registers.A = result;
}

void DAA_0x27(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    long a = cpu->registers.A;

    if (!cpu->is_flag_set(Flags::AddSubFlag))
    {
        if (cpu->is_flag_set(Flags::HalfCarryFlag) || (a & 0xF) > 9)
        {
            a += 0x06;
        }

        if (cpu->is_flag_set(Flags::CarryFlag) || a > 0x9F)
        {
            a += 0x60;
        }
    }
    else
    {
        if (cpu->is_flag_set(Flags::HalfCarryFlag))
        {
            a = (a - 6) & 0xFF;
        }

        if (cpu->is_flag_set(Flags::CarryFlag))
        {
            a -= 0x60;
        }
    }

    long F = cpu->registers.F;
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

    cpu->registers.F = F;
    cpu->registers.A = a;

    toggle_zero_flag(cpu, a);
}

void DEC_0x35(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->enable_flag(Flags::AddSubFlag);
    cpu->disable_flag(Flags::ZeroFlag);

    long HL = cpu->registers.HL;
    long val = (cpu->memory.read8(HL) - 1) & 0xFF;

    cpu->tick(4);

    if ((val & 0xF) == 0xF)
    {
        cpu->enable_flag(Flags::HalfCarryFlag);
    }
    else
    {
        cpu->disable_flag(Flags::HalfCarryFlag);
    }

    toggle_zero_flag(cpu, val);

    cpu->memory.write8(HL, val);

    cpu->tick(4);
    cpu->tick(4);
}

void SCF_0x37(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->disable_flag(Flags::AddSubFlag);
    cpu->disable_flag(Flags::HalfCarryFlag);
    cpu->enable_flag(Flags::CarryFlag);
}

void LD_0x3A(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.A = cpu->memory.read8(cpu->registers.HL);
    cpu->registers.HL--;
}

void CCF_0x3F(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->disable_flag(Flags::AddSubFlag);
    cpu->disable_flag(Flags::HalfCarryFlag);

    if (cpu->is_flag_set(Flags::CarryFlag))
    {
        cpu->disable_flag(Flags::CarryFlag);
    }
    else
    {
        cpu->enable_flag(Flags::CarryFlag);
    }
}

void HALT_0x76(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->set_wait_for_interrupt(true);
}

void ADC_0x8F(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    long target = opcode & 0xF;
    long number = 0;

    if (target == 14)
    {
        long memoryFlag = (opcode & 0b01000000) == 0;

        if (memoryFlag)
        {
            ADD(RegisterType::HL, true, cpu, false);
        }
        else
        {
            number = cpu->read_u8();
            ADD(number, true, cpu, true);
        }

        return;
    }

    long reg = RegisterType::HL;

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

    ADD(reg, true, cpu, false);
}

void SUB_0x96(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    SUB(RegisterType::HL, false, cpu, false);
}

void SBC_0xDE(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    long target = opcode & 0xF;
    long number = 0;

    if (target == 14)
    {
        long memoryFlag = (opcode & 0b01000000) == 0;

        if (memoryFlag)
        {
            SUB(RegisterType::HL, true, cpu, false);
        }
        else
        {
            number = cpu->read_u8();
            SUB(number, true, cpu, true);
        }

        return;
    }
    
    long reg = RegisterType::HL;

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

    SUB(reg, true, cpu, false);
}

void AND_0xA6(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    long val = cpu->memory.read8(cpu->registers.HL);
    long result = cpu->registers.A & val;

    cpu->clear_flags();
    cpu->registers.A = result;

    toggle_zero_flag(cpu, result);

    cpu->enable_flag(Flags::HalfCarryFlag);
}

void XOR_0xAE(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    long val = cpu->memory.read8(cpu->registers.HL);
    long result = cpu->registers.A ^ val;

    cpu->clear_flags();
    cpu->registers.A = result;

    toggle_zero_flag(cpu, result);
}

void OR_0xB6(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    long val = cpu->memory.read8(cpu->registers.HL);
    long result = cpu->registers.A | val;

    cpu->clear_flags();
    cpu->registers.A = result;

    toggle_zero_flag(cpu, result);
}

void CP_0xB8(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    CP(cpu->registers.B, cpu);
}

void CP_0xB9(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    CP(cpu->registers.C, cpu);
}

void CP_0xBA(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    CP(cpu->registers.D, cpu);
}

void CP_0xBB(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    CP(cpu->registers.E, cpu);
}

void CP_0xBC(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    CP(cpu->registers.H, cpu);
}

void CP_0xBD(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    CP(cpu->registers.L, cpu);
}

void CP_0xBF(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    CP(cpu->registers.A, cpu);
}

void CALL_0xC4(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    long addr = cpu->read_u16();
    bool check = false;

    switch ((opcode >> 3) & 0x03)
    {
        case 0x00:
            check = !cpu->is_flag_set(Flags::ZeroFlag);
            break;

        case 0x01:
            check = cpu->is_flag_set(Flags::ZeroFlag);
            break;

        case 0x02:
            check = !cpu->is_flag_set(Flags::CarryFlag);
            break;

        case 0x03:
            check = cpu->is_flag_set(Flags::CarryFlag);
            break;
    }

    if (check)
    {
        cpu->push_stack(cpu->registers.PC);
        cpu->registers.PC = addr;
        instruction->ticks += 12;
    }
}

void ADD_0xC6(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    ADD(cpu->read_u8(), false, cpu, true);
}

void SUB_0xD6(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    SUB(cpu->read_u8(), false, cpu, true);
}

void ADD_0xE8(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->clear_flags();
    
    long value = cpu->read_s8();
    long sp = cpu->registers.SP;

    long result = sp + value;

    if (((sp ^ value ^ (result & 0xFFFF)) & 0x100) == 0x100)
    {
        cpu->enable_flag(Flags::CarryFlag);
    }

    if (((sp ^ value ^ (result & 0xFFFF)) & 0x10) == 0x10)
    {
        cpu->enable_flag(Flags::HalfCarryFlag);
    }

    cpu->registers.SP = result;
}

void XOR_0xEE(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    long val = cpu->read_u8();
    long result = cpu->registers.A ^ val;

    cpu->clear_flags();
    cpu->registers.A = result;

    toggle_zero_flag(cpu, result);
}

void LD_0xF2(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.A = cpu->memory.read8(0xFF00 + cpu->registers.C);
}

void OR_0xF6(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    long val = cpu->read_u8();
    long result = cpu->registers.A | val;

    cpu->clear_flags();
    cpu->registers.A = result;

    toggle_zero_flag(cpu, result);
}

void LD_0xF8(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->clear_flags();

    long SP = cpu->registers.SP;
    int8_t val = cpu->read_s8();
    long result = (SP + val) & 0xFFFF;

    if (((SP ^ val ^ result) & 0x100) == 0x100)
    {
        cpu->enable_flag(Flags::CarryFlag);
    }

    if (((SP ^ val ^ result) & 0x10) == 0x10)
    {
        cpu->enable_flag(Flags::HalfCarryFlag);
    }
    
    cpu->registers.HL = result;
}

void LD_0xF9(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->registers.SP = cpu->registers.HL;
}

void SRL_0x38(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->tick(4);

    long reg = cpu->read_byte_register_type(opcode, true);

    SRL(reg, cpu);
}

void RLC_0x00(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->tick(4);

    long reg = cpu->read_byte_register_type(opcode, true);
    long value = 0;

    cpu->disable_flag(Flags::HalfCarryFlag);
    cpu->disable_flag(Flags::AddSubFlag);

    switch (reg)
    {
        case RegisterType::B:
            value = cpu->registers.B;
            break;

        case RegisterType::C:
            value = cpu->registers.C;
            break;

        case RegisterType::D:
            value = cpu->registers.D;
            break;

        case RegisterType::E:
            value = cpu->registers.E;
            break;

        case RegisterType::H:
            value = cpu->registers.H;
            break;

        case RegisterType::L:
            value = cpu->registers.L;
            break;

        case RegisterType::HL:
            value = cpu->memory.read8(cpu->registers.HL);
            cpu->tick(4);
            break;

        case RegisterType::A:
            value = cpu->registers.A;
            break;
    }

    long carry = !!(value&0x80);

    if (carry)
    {
        cpu->enable_flag(Flags::CarryFlag);
    }
    else
    {
        cpu->disable_flag(Flags::CarryFlag);
    }

    long result = ((value << 1) & 0xFF) | (carry);

    switch (reg)
    {
        case RegisterType::B:
            cpu->registers.B = result;
            break;

        case RegisterType::C:
            cpu->registers.C = result;
            break;

        case RegisterType::D:
            cpu->registers.D = result;
            break;

        case RegisterType::E:
            cpu->registers.E = result;
            break;

        case RegisterType::H:
            cpu->registers.H = result;
            break;

        case RegisterType::L:
            cpu->registers.L = result;
            break;

        case RegisterType::A:
            cpu->registers.A = result;
            break;
        
        case RegisterType::HL:
            cpu->memory.write8(cpu->registers.HL, result);
            cpu->tick(4);
            break;
    }

    toggle_zero_flag(cpu, result);
    cpu->tick(4);
}

void RRC_0x08(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->tick(4);

    long reg = cpu->read_byte_register_type(opcode, true);
    long value = 0;

    cpu->clear_flags();

    switch (reg)
    {
        case RegisterType::B:
            value = cpu->registers.B;
            break;

        case RegisterType::C:
            value = cpu->registers.C;
            break;

        case RegisterType::D:
            value = cpu->registers.D;
            break;

        case RegisterType::E:
            value = cpu->registers.E;
            break;

        case RegisterType::H:
            value = cpu->registers.H;
            break;

        case RegisterType::L:
            value = cpu->registers.L;
            break;

        case RegisterType::HL:
            value = cpu->memory.read8(cpu->registers.HL);
            cpu->tick(4);
            break;

        case RegisterType::A:
            value = cpu->registers.A;
            break;
    }

    if ((value & 0x01) != 0)
    {
        cpu->enable_flag(Flags::CarryFlag);

        value >>= 1;
        value |= 0x80;
    }
    else
    {
        value >>= 1;
    }

    switch (reg)
    {
        case RegisterType::B:
            cpu->registers.B = value;
            break;

        case RegisterType::C:
            cpu->registers.C = value;
            break;

        case RegisterType::D:
            cpu->registers.D = value;
            break;

        case RegisterType::E:
            cpu->registers.E = value;
            break;

        case RegisterType::H:
            cpu->registers.H = value;
            break;

        case RegisterType::L:
            cpu->registers.L = value;
            break;

        case RegisterType::A:
            cpu->registers.A = value;
            break;
        
        case RegisterType::HL:
            cpu->memory.write8(cpu->registers.HL, value);
            cpu->tick(4);
            break;
    }

    toggle_zero_flag(cpu, value);
    cpu->tick(4);
}

void RR_0x19(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->tick(4);

    long reg = cpu->read_byte_register_type(opcode, true);
    long value = 0;

    switch (reg)
    {
        case RegisterType::B:
            value = cpu->registers.B;
            break;

        case RegisterType::C:
            value = cpu->registers.C;
            break;

        case RegisterType::D:
            value = cpu->registers.D;
            break;

        case RegisterType::E:
            value = cpu->registers.E;
            break;

        case RegisterType::H:
            value = cpu->registers.H;
            break;

        case RegisterType::L:
            value = cpu->registers.L;
            break;

        case RegisterType::HL:
            value = cpu->memory.read8(cpu->registers.HL);
            cpu->tick(4);
            break;

        case RegisterType::A:
            value = cpu->registers.A;
            break;
    }

    long carry = cpu->is_flag_set(Flags::CarryFlag) ? 0x80 : 0;

    cpu->clear_flags();

    if ((value & 0x01) != 0)
    {
        cpu->enable_flag(Flags::CarryFlag);
    }

    value >>= 1;
    value |= carry;

    switch (reg)
    {
        case RegisterType::B:
            cpu->registers.B = value;
            break;

        case RegisterType::C:
            cpu->registers.C = value;
            break;

        case RegisterType::D:
            cpu->registers.D = value;
            break;

        case RegisterType::E:
            cpu->registers.E = value;
            break;

        case RegisterType::H:
            cpu->registers.H = value;
            break;

        case RegisterType::L:
            cpu->registers.L = value;
            break;

        case RegisterType::A:
            cpu->registers.A = value;
            break;
        
        case RegisterType::HL:
            cpu->memory.write8(cpu->registers.HL, value);
            cpu->tick(4);
            break;
    }

    toggle_zero_flag(cpu, value);
    cpu->tick(4);
}

void SLA_0x20(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->tick(4);

    long reg = cpu->read_byte_register_type(opcode, true);
    long value = 0;

    switch (reg)
    {
        case RegisterType::B:
            value = cpu->registers.B;
            break;

        case RegisterType::C:
            value = cpu->registers.C;
            break;

        case RegisterType::D:
            value = cpu->registers.D;
            break;

        case RegisterType::E:
            value = cpu->registers.E;
            break;

        case RegisterType::H:
            value = cpu->registers.H;
            break;

        case RegisterType::L:
            value = cpu->registers.L;
            break;

        case RegisterType::HL:
            value = cpu->memory.read8(cpu->registers.HL);
            cpu->tick(4);
            break;

        case RegisterType::A:
            value = cpu->registers.A;
            break;
    }

    cpu->disable_flag(Flags::HalfCarryFlag);
    cpu->disable_flag(Flags::AddSubFlag);

    if (value > 0x7F)
    {
        cpu->enable_flag(Flags::CarryFlag);
    }
    else
    {
        cpu->disable_flag(Flags::CarryFlag);
    }
    
    long result = (value << 1) & 0xFF;

    switch (reg)
    {
        case RegisterType::B:
            cpu->registers.B = result;
            break;

        case RegisterType::C:
            cpu->registers.C = result;
            break;

        case RegisterType::D:
            cpu->registers.D = result;
            break;

        case RegisterType::E:
            cpu->registers.E = result;
            break;

        case RegisterType::H:
            cpu->registers.H = result;
            break;

        case RegisterType::L:
            cpu->registers.L = result;
            break;

        case RegisterType::A:
            cpu->registers.A = result;
            break;
        
        case RegisterType::HL:
            cpu->memory.write8(cpu->registers.HL, result);
            cpu->tick(4);
            break;
    }

    toggle_zero_flag(cpu, result);
    cpu->tick(4);
}

void SRA_0x28(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->tick(4);

    long reg = cpu->read_byte_register_type(opcode, true);
    long result = 0;

    switch (reg)
    {
        case RegisterType::B:
            result = cpu->registers.B;
            break;

        case RegisterType::C:
            result = cpu->registers.C;
            break;

        case RegisterType::D:
            result = cpu->registers.D;
            break;

        case RegisterType::E:
            result = cpu->registers.E;
            break;

        case RegisterType::H:
            result = cpu->registers.H;
            break;

        case RegisterType::L:
            result = cpu->registers.L;
            break;

        case RegisterType::HL:
            result = cpu->memory.read8(cpu->registers.HL);
            cpu->tick(4);
            break;

        case RegisterType::A:
            result = cpu->registers.A;
            break;
    }

    cpu->clear_flags();

    if ((result & 0x01) != 0) {
        cpu->enable_flag(Flags::CarryFlag);
    }

    if ((result & 0x80) != 0) {
        result >>= 1;
        result |= 0x80;
    } else {
        result >>= 1;
    }

    switch (reg)
    {
        case RegisterType::B:
            cpu->registers.B = result;
            break;

        case RegisterType::C:
            cpu->registers.C = result;
            break;

        case RegisterType::D:
            cpu->registers.D = result;
            break;

        case RegisterType::E:
            cpu->registers.E = result;
            break;

        case RegisterType::H:
            cpu->registers.H = result;
            break;

        case RegisterType::L:
            cpu->registers.L = result;
            break;

        case RegisterType::A:
            cpu->registers.A = result;
            break;
        
        case RegisterType::HL:
            cpu->memory.write8(cpu->registers.HL, result);
            cpu->tick(4);
            break;
    }

    toggle_zero_flag(cpu, result);
    cpu->tick(4);
}

void SET_0xC0(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    cpu->tick(4);

    long reg = cpu->read_byte_register_type(opcode, true);
    long bit = (opcode & 0b00111000) >> 3;

    long result = 0;
    switch (reg)
    {
        case RegisterType::B:
            result = cpu->registers.B;
            break;

        case RegisterType::C:
            result = cpu->registers.C;
            break;

        case RegisterType::D:
            result = cpu->registers.D;
            break;

        case RegisterType::E:
            result = cpu->registers.E;
            break;

        case RegisterType::H:
            result = cpu->registers.H;
            break;

        case RegisterType::L:
            result = cpu->registers.L;
            break;

        case RegisterType::HL:
            result = cpu->memory.read8(cpu->registers.HL);
            cpu->tick(4);
            break;

        case RegisterType::A:
            result = cpu->registers.A;
            break;
    }

    result |= (1 << bit);

    switch (reg)
    {
        case RegisterType::B:
            cpu->registers.B = result;
            break;

        case RegisterType::C:
            cpu->registers.C = result;
            break;

        case RegisterType::D:
            cpu->registers.D = result;
            break;

        case RegisterType::E:
            cpu->registers.E = result;
            break;

        case RegisterType::H:
            cpu->registers.H = result;
            break;

        case RegisterType::L:
            cpu->registers.L = result;
            break;

        case RegisterType::A:
            cpu->registers.A = result;
            break;
        
        case RegisterType::HL:
            cpu->memory.write8(cpu->registers.HL, result);
            cpu->tick(4);
            break;
    }

    cpu->tick(4);
}