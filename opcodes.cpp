#include "opcodes.h"
#include "gameboy_cpu.h"

void LD_0x01x11x21x31(Instruction instruction)
{
    auto val = instruction.cpu->read_u16();
    auto reg = instruction.cpu->read_register_type(instruction.opcode >> 4, false);

    instruction.cpu->set(reg, val);
}