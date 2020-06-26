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

void LD_0x01x11x21x31(Instruction instruction)
{
    auto val = instruction.cpu->read_u16();
    auto reg = instruction.cpu->read_register_type(instruction.opcode >> 4, false);

    instruction.cpu->set(reg, val);
}

void XOR_0xA9(Instruction instruction)
{
    auto reg = instruction.cpu->read_byte_register_type(instruction.opcode);
    auto result = instruction.cpu->get(RegisterType::A) ^ instruction.cpu->get(reg);

    instruction.cpu->clear_flags();
    instruction.cpu->set(RegisterType::A, result);

    toggle_zero_flag(instruction.cpu, result);
}

void LD_0x32(Instruction instruction)
{
    instruction.cpu->get_memory()->write8(instruction.cpu->get(RegisterType::HL), instruction.cpu->get(RegisterType::A));
    instruction.cpu->decrement(RegisterType::HL);
}

void JR_0x20(Instruction instruction)
{
    auto relative = instruction.cpu->read_s8();
    bool check = false;

    switch ((instruction.opcode >> 3) & 0x03)
    {
        case 0x00:
            check = !instruction.cpu->is_flag_set(Flags::ZeroFlag);
            break;

        case 0x01:
            check = instruction.cpu->is_flag_set(Flags::ZeroFlag);
            break;

        case 0x02:
            check = !instruction.cpu->is_flag_set(Flags::CarryFlag);
            break;

        case 0x03:
            check = instruction.cpu->is_flag_set(Flags::CarryFlag);
            break;
    }

    if (check)
    {
        instruction.cpu->increment(RegisterType::PC, relative);
        instruction.ticks += 4;
    }
}

void LD_0x06(Instruction instruction)
{
    auto reg = instruction.cpu->read_byte_register_type(instruction.opcode >> 3);
    auto val = instruction.cpu->read_u8();

    instruction.cpu->set(reg, val);
}

void LD_0xE2(Instruction instruction)
{
    instruction.cpu->get_memory()->write8(0xFF00 + instruction.cpu->get(RegisterType::C), instruction.cpu->get(RegisterType::A));
}

void BIT_0x7C(Instruction instruction)
{
    instruction.cpu->cycle(4);

    auto reg = instruction.cpu->read_byte_register_type(instruction.opcode);
    auto bit = (instruction.opcode & 0b00111000) >> 3;

    if ((instruction.opcode & 0x7) == 6)
    {
        BIT_Impl(RegisterType::None, bit, instruction.cpu);
    }
    else
    {
        BIT_Impl(reg, bit, instruction.cpu);
    }
}
