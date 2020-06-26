#include "gameboy_cpu.h"
#include "memory.h"
#include "opcodes.h"

GameboyCPU::GameboyCPU(GxEPD_Class* display) : registers()
{
    memory = new Memory(this);
    this->display = display;
}

void GameboyCPU::tick(long num_cycles)
{

}

void GameboyCPU::set_bios(File bios)
{
    memory->set_bios(bios);
}

void GameboyCPU::set_rom(File rom)
{
    memory->set_rom(rom);
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

        Serial.println("TODO: implement CB opcodes");
        // instruction.ticks = _cbopcodes[instruction.opcode][0];
        // instruction.exec = _cbopcodes[instruction.opcode][1];

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

        display->println("Invalid opcode: " + String(hex));
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

long GameboyCPU::set(RegisterType reg, long val)
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
            this._registers16[2] = value;

            this._registers[Register.A] = this._registers16[2] >> 8;
            this._registers[Register.F] = this._registers16[2] & 0xFF;
            
            return this._registers16[2];

        case RegisterType::SP:
            this._registers16[0] = value;
            return this._registers16[0];

        case RegisterType::PC:
            this._registers16[1] = value;
            return this._registers16[1];

        case RegisterType::BC:
            this._registers16[2] = value;

            this._registers[Register.B] = this._registers16[2] >> 8;
            this._registers[Register.C] = this._registers16[2] & 0xFF;

            return this._registers16[2];

        case RegisterType::DE:
            this._registers16[2] = value;

            this._registers[Register.D] = this._registers16[2] >> 8;
            this._registers[Register.E] = this._registers16[2] & 0xFF;

            return this._registers16[2];

        case RegisterType::HL:
            this._registers16[2] = value;

            this._registers[Register.H] = this._registers16[2] >> 8;
            this._registers[Register.L] = this._registers16[2] & 0xFF;

            return this._registers16[2];
    }
}