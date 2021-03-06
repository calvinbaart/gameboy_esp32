#ifndef _OPCODES_H_
#define _OPCODES_H_

#include "gameboy_cpu.h"

extern void LD_0x01(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x11(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x21(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x31(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void XOR_0xA8(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void XOR_0xA9(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void XOR_0xAA(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void XOR_0xAB(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void XOR_0xAC(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void XOR_0xAD(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void XOR_0xAF(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x32(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void JR_0x20(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x06(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x0E(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x16(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x1E(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x26(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x2E(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x3E(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0xE2(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x70(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x71(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x72(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x73(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x74(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x75(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x77(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LDH_0xE0(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x1A(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void INC_0x04(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void INC_0x0C(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void INC_0x14(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void INC_0x1C(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void INC_0x24(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void INC_0x2C(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void INC_0x3C(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void CALL_0xCD(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x40(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x41(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x42(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x43(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x44(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x45(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x47(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x48(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x49(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x4A(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x4B(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x4C(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x4D(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x4F(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x50(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x51(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x52(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x53(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x54(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x55(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x57(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x58(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x59(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x5A(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x5B(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x5C(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x5D(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x5F(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x60(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x61(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x62(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x63(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x64(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x65(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x67(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x68(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x69(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x6A(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x6B(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x6C(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x6D(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x6F(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x78(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x79(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x7A(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x7B(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x7C(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x7D(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x7F(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x22(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void PUSH_0xC5(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void PUSH_0xD5(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void PUSH_0xE5(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void PUSH_0xF5(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void POP_0xC1(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void POP_0xD1(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void POP_0xE1(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void POP_0xF1(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void RLA_0x17(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void DEC_0x05(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void DEC_0x0D(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void DEC_0x15(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void DEC_0x1D(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void DEC_0x25(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void DEC_0x2D(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void DEC_0x3D(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void INC_0x03(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void INC_0x13(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void INC_0x23(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void INC_0x33(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void RET_0xC9(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void CP_0xFE(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0xEA(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void JR_0x18(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LDH_0xF0(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void SUB_0x90(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void CP_0xBE(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void ADD_0x86(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void JP_0xC3(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void DI_0xF3(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x36(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x2A(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void DEC_0x0B(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void DEC_0x1B(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void DEC_0x2B(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void DEC_0x3B(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void OR_0xB0(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void OR_0xB1(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void OR_0xB2(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void OR_0xB3(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void OR_0xB4(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void OR_0xB5(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void OR_0xB7(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void EI_0xFB(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void AND_0xA0(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void AND_0xA1(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void AND_0xA2(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void AND_0xA3(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void AND_0xA4(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void AND_0xA5(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void AND_0xA7(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void RET_0xC0(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0xFA(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void INC_0x34(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void RETI_0xD9(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void CPL_0x2F(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void AND_0xE6(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void RST_0xEF(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void ADD_0x81(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void ADD_0x09(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void ADD_0x19(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void ADD_0x29(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void ADD_0x39(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x46(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x4E(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x56(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x5E(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x66(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x6E(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x7E(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void JP_0xE9(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x12(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void JP_0xC2(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x02(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void RLCA_0x07(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x08(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x0A(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void RRCA_0x0F(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void RRA_0x1F(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void DAA_0x27(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void DEC_0x35(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void SCF_0x37(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0x3A(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void CCF_0x3F(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void HALT_0x76(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void ADC_0x8F(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void SUB_0x96(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void SBC_0xDE(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void AND_0xA6(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void XOR_0xAE(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void OR_0xB6(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void CP_0xB8(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void CP_0xB9(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void CP_0xBA(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void CP_0xBB(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void CP_0xBC(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void CP_0xBD(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void CP_0xBF(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void CALL_0xC4(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void ADD_0xC6(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void SUB_0xD6(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void ADD_0xE8(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void XOR_0xEE(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0xF2(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void OR_0xF6(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0xF8(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void LD_0xF9(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);

// CB
extern void BIT_0x7C(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void RL_0x11(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void SWAP_0x37(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void RES_0x87(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void SRL_0x38(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void RLC_0x00(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void RRC_0x08(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void RR_0x19(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void SLA_0x20(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void SRA_0x28(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);
extern void SET_0xC0(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction);

static void NOP_0x00(uint8_t opcode, GameboyCPU* cpu, Instruction* instruction)
{
    // NOP
}

static void (*opcodes[])(uint8_t, GameboyCPU*, Instruction*) = {
    &NOP_0x00, //0x00
    &LD_0x01, //0x01
    &LD_0x02, //0x02
    &INC_0x03, //0x03
    &INC_0x04, //0x04
    &DEC_0x05, //0x05
    &LD_0x06, //0x06
    &RLCA_0x07, //0x07
    &LD_0x08, //0x08
    &ADD_0x09, //0x09
    &LD_0x0A, //0x0A
    &DEC_0x0B, //0x0B
    &INC_0x0C, //0x0C
    &DEC_0x0D, //0x0D
    &LD_0x0E, //0x0E
    &RRCA_0x0F, //0x0F
    &NOP_0x00, //0x10 (STOP)
    &LD_0x11, //0x11
    &LD_0x12, //0x12
    &INC_0x13, //0x13
    &INC_0x14, //0x14
    &DEC_0x15, //0x15
    &LD_0x16, //0x16
    &RLA_0x17, //0x17
    &JR_0x18, //0x18
    &ADD_0x19, //0x19
    &LD_0x1A, //0x1A
    &DEC_0x1B, //0x1B
    &INC_0x1C, //0x1C
    &DEC_0x1D, //0x1D
    &LD_0x1E, //0x1E
    &RRA_0x1F, //0x1F
    &JR_0x20, //0x20
    &LD_0x21, //0x21
    &LD_0x22, //0x22
    &INC_0x23, //0x23
    &INC_0x24, //0x24
    &DEC_0x25, //0x25
    &LD_0x26, //0x26
    &DAA_0x27, //0x27
    &JR_0x20, //0x28
    &ADD_0x29, //0x29
    &LD_0x2A, //0x2A
    &DEC_0x2B, //0x2B
    &INC_0x2C, //0x2C
    &DEC_0x2D, //0x2D
    &LD_0x2E, //0x2E
    &CPL_0x2F, //0x2F
    &JR_0x20, //0x30
    &LD_0x31, //0x31
    &LD_0x32, //0x32
    &INC_0x33, //0x33
    &INC_0x34, //0x34
    &DEC_0x35, //0x35
    &LD_0x36, //0x36
    &SCF_0x37, //0x37
    &JR_0x20, //0x38
    &ADD_0x39, //0x39
    &LD_0x3A, //0x3A
    &DEC_0x3B, //0x3B
    &INC_0x3C, //0x3C
    &DEC_0x3D, //0x3D
    &LD_0x3E, //0x3E
    &CCF_0x3F, //0x3F
    &LD_0x40, //0x40
    &LD_0x41, //0x41
    &LD_0x42, //0x42
    &LD_0x43, //0x43
    &LD_0x44, //0x44
    &LD_0x45, //0x45
    &LD_0x46, //0x46
    &LD_0x47, //0x47
    &LD_0x48, //0x48
    &LD_0x49, //0x49
    &LD_0x4A, //0x4A
    &LD_0x4B, //0x4B
    &LD_0x4C, //0x4C
    &LD_0x4D, //0x4D
    &LD_0x4E, //0x4E
    &LD_0x4F, //0x4F
    &LD_0x50, //0x50
    &LD_0x51, //0x51
    &LD_0x52, //0x52
    &LD_0x53, //0x53
    &LD_0x54, //0x54
    &LD_0x55, //0x55
    &LD_0x56, //0x56
    &LD_0x57, //0x57
    &LD_0x58, //0x58
    &LD_0x59, //0x59
    &LD_0x5A, //0x5A
    &LD_0x5B, //0x5B
    &LD_0x5C, //0x5C
    &LD_0x5D, //0x5D
    &LD_0x5E, //0x5E
    &LD_0x5F, //0x5F
    &LD_0x60, //0x60
    &LD_0x61, //0x61
    &LD_0x62, //0x62
    &LD_0x63, //0x63
    &LD_0x64, //0x64
    &LD_0x65, //0x65
    &LD_0x66, //0x66
    &LD_0x67, //0x67
    &LD_0x68, //0x68
    &LD_0x69, //0x69
    &LD_0x6A, //0x6A
    &LD_0x6B, //0x6B
    &LD_0x6C, //0x6C
    &LD_0x6D, //0x6D
    &LD_0x6E, //0x6E
    &LD_0x6F, //0x6F
    &LD_0x70, //0x70
    &LD_0x71, //0x71
    &LD_0x72, //0x72
    &LD_0x73, //0x73
    &LD_0x74, //0x74
    &LD_0x75, //0x75
    &HALT_0x76, //0x76
    &LD_0x77, //0x77
    &LD_0x78, //0x78
    &LD_0x79, //0x79
    &LD_0x7A, //0x7A
    &LD_0x7B, //0x7B
    &LD_0x7C, //0x7C
    &LD_0x7D, //0x7D
    &LD_0x7E, //0x7E
    &LD_0x7F, //0x7F
    &ADD_0x81, //0x80
    &ADD_0x81, //0x81
    &ADD_0x81, //0x82
    &ADD_0x81, //0x83
    &ADD_0x81, //0x84
    &ADD_0x81, //0x85
    &ADD_0x86, //0x86
    &ADD_0x81, //0x87
    &ADC_0x8F, //0x88
    &ADC_0x8F, //0x89
    &ADC_0x8F, //0x8A
    &ADC_0x8F, //0x8B
    &ADC_0x8F, //0x8C
    &ADC_0x8F, //0x8D
    &ADC_0x8F, //0x8E
    &ADC_0x8F, //0x8F
    &SUB_0x90, //0x90
    &SUB_0x90, //0x91
    &SUB_0x90, //0x92
    &SUB_0x90, //0x93
    &SUB_0x90, //0x94
    &SUB_0x90, //0x95
    &SUB_0x96, //0x96
    &SUB_0x90, //0x97
    &SBC_0xDE, //0x98
    &SBC_0xDE, //0x99
    &SBC_0xDE, //0x9A
    &SBC_0xDE, //0x9B
    &SBC_0xDE, //0x9C
    &SBC_0xDE, //0x9D
    &SBC_0xDE, //0x9E
    &SBC_0xDE, //0x9F
    &AND_0xA0, //0xA0
    &AND_0xA1, //0xA1
    &AND_0xA2, //0xA2
    &AND_0xA3, //0xA3
    &AND_0xA4, //0xA4
    &AND_0xA5, //0xA5
    &AND_0xA6, //0xA6
    &AND_0xA7, //0xA7
    &XOR_0xA8, //0xA8
    &XOR_0xA9, //0xA9
    &XOR_0xAA, //0xAA
    &XOR_0xAB, //0xAB
    &XOR_0xAC, //0xAC
    &XOR_0xAD, //0xAD
    &XOR_0xAE, //0xAE
    &XOR_0xAF, //0xAF
    &OR_0xB0, //0xB0
    &OR_0xB1, //0xB1
    &OR_0xB2, //0xB2
    &OR_0xB3, //0xB3
    &OR_0xB4, //0xB4
    &OR_0xB5, //0xB5
    &OR_0xB6, //0xB6
    &OR_0xB7, //0xB7
    &CP_0xB8, //0xB8
    &CP_0xB9, //0xB9
    &CP_0xBA, //0xBA
    &CP_0xBB, //0xBB
    &CP_0xBC, //0xBC
    &CP_0xBD, //0xBD
    &CP_0xBE, //0xBE
    &CP_0xBF, //0xBF
    &RET_0xC0, //0xC0
    &POP_0xC1, //0xC1
    &JP_0xC2, //0xC2
    &JP_0xC3, //0xC3
    &CALL_0xC4, //0xC4
    &PUSH_0xC5, //0xC5
    &ADD_0xC6, //0xC6
    &RST_0xEF, //0xC7
    &RET_0xC0, //0xC8
    &RET_0xC9, //0xC9
    &JP_0xC2, //0xCA
    nullptr, //0xCB
    &CALL_0xC4, //0xCC
    &CALL_0xCD, //0xCD
    &ADC_0x8F, //0xCE
    &RST_0xEF, //0xCF
    &RET_0xC0, //0xD0
    &POP_0xD1, //0xD1
    &JP_0xC2, //0xD2
    nullptr, //0xD3
    &CALL_0xC4, //0xD4
    &PUSH_0xD5, //0xD5
    &SUB_0xD6, //0xD6
    &RST_0xEF, //0xD7
    &RET_0xC0, //0xD8
    &RETI_0xD9, //0xD9
    &JP_0xC2, //0xDA
    nullptr, //0xDB
    &CALL_0xC4, //0xDC
    nullptr, //0xDD
    &SBC_0xDE, //0xDE
    &RST_0xEF, //0xDF
    &LDH_0xE0, //0xE0
    &POP_0xE1, //0xE1
    &LD_0xE2, //0xE2
    nullptr, //0xE3
    nullptr, //0xE4
    &PUSH_0xE5, //0xE5
    &AND_0xE6, //0xE6
    &RST_0xEF, //0xE7
    &ADD_0xE8, //0xE8
    &JP_0xE9, //0xE9
    &LD_0xEA, //0xEA
    nullptr, //0xEB
    nullptr, //0xEC
    nullptr, //0xED
    &XOR_0xEE, //0xEE
    &RST_0xEF, //0xEF
    &LDH_0xF0, //0xF0
    &POP_0xF1, //0xF1
    &LD_0xF2, //0xF2
    &DI_0xF3, //0xF3
    nullptr, //0xF4
    &PUSH_0xF5, //0xF5
    &OR_0xF6, //0xF6
    &RST_0xEF, //0xF7
    &LD_0xF8, //0xF8
    &LD_0xF9, //0xF9
    &LD_0xFA, //0xFA
    &EI_0xFB, //0xFB
    nullptr, //0xFC
    nullptr, //0xFD
    &CP_0xFE, //0xFE
    &RST_0xEF, //0xFF
};

static int opcode_ticks[] = {
    4, //0x00
    12, //0x01
    8, //0x02
    8, //0x03
    4, //0x04
    4, //0x05
    8, //0x06
    4, //0x07
    20, //0x08
    8, //0x09
    8, //0x0A
    8, //0x0B
    4, //0x0C
    4, //0x0D
    8, //0x0E
    4, //0x0F
    0, //0x10
    12, //0x11
    8, //0x12
    8, //0x13
    4, //0x14
    4, //0x15
    8, //0x16
    4, //0x17
    12, //0x18
    8, //0x19
    8, //0x1A
    8, //0x1B
    4, //0x1C
    4, //0x1D
    8, //0x1E
    4, //0x1F
    8, //0x20
    12, //0x21
    8, //0x22
    8, //0x23
    4, //0x24
    4, //0x25
    8, //0x26
    4, //0x27
    8, //0x28
    8, //0x29
    8, //0x2A
    8, //0x2B
    4, //0x2C
    4, //0x2D
    8, //0x2E
    4, //0x2F
    8, //0x30
    12, //0x31
    8, //0x32
    8, //0x33
    0, //0x34
    0, //0x35
    0, //0x36
    4, //0x37
    8, //0x38
    8, //0x39
    8, //0x3A
    8, //0x3B
    4, //0x3C
    4, //0x3D
    8, //0x3E
    4, //0x3F
    4, //0x40
    4, //0x41
    4, //0x42
    4, //0x43
    4, //0x44
    4, //0x45
    8, //0x46
    4, //0x47
    4, //0x48
    4, //0x49
    4, //0x4A
    4, //0x4B
    4, //0x4C
    4, //0x4D
    8, //0x4E
    4, //0x4F
    4, //0x50
    4, //0x51
    4, //0x52
    4, //0x53
    4, //0x54
    4, //0x55
    8, //0x56
    4, //0x57
    4, //0x58
    4, //0x59
    4, //0x5A
    4, //0x5B
    4, //0x5C
    4, //0x5D
    8, //0x5E
    4, //0x5F
    4, //0x60
    4, //0x61
    4, //0x62
    4, //0x63
    4, //0x64
    4, //0x65
    8, //0x66
    4, //0x67
    4, //0x68
    4, //0x69
    4, //0x6A
    4, //0x6B
    4, //0x6C
    4, //0x6D
    8, //0x6E
    4, //0x6F
    8, //0x70
    8, //0x71
    8, //0x72
    8, //0x73
    8, //0x74
    8, //0x75
    0, //0x76
    8, //0x77
    4, //0x78
    4, //0x79
    4, //0x7A
    4, //0x7B
    4, //0x7C
    4, //0x7D
    8, //0x7E
    4, //0x7F
    4, //0x80
    4, //0x81
    4, //0x82
    4, //0x83
    4, //0x84
    4, //0x85
    8, //0x86
    4, //0x87
    4, //0x88
    4, //0x89
    4, //0x8A
    4, //0x8B
    4, //0x8C
    4, //0x8D
    8, //0x8E
    4, //0x8F
    4, //0x90
    4, //0x91
    4, //0x92
    4, //0x93
    4, //0x94
    4, //0x95
    8, //0x96
    4, //0x97
    4, //0x98
    4, //0x99
    4, //0x9A
    4, //0x9B
    4, //0x9C
    4, //0x9D
    8, //0x9E
    4, //0x9F
    4, //0xA0
    4, //0xA1
    4, //0xA2
    4, //0xA3
    4, //0xA4
    4, //0xA5
    8, //0xA6
    4, //0xA7
    4, //0xA8
    4, //0xA9
    4, //0xAA
    4, //0xAB
    4, //0xAC
    4, //0xAD
    8, //0xAE
    4, //0xAF
    4, //0xB0
    4, //0xB1
    4, //0xB2
    4, //0xB3
    4, //0xB4
    4, //0xB5
    8, //0xB6
    4, //0xB7
    4, //0xB8
    4, //0xB9
    4, //0xBA
    4, //0xBB
    4, //0xBC
    4, //0xBD
    8, //0xBE
    4, //0xBF
    8, //0xC0
    12, //0xC1
    12, //0xC2
    16, //0xC3
    12, //0xC4
    16, //0xC5
    8, //0xC6
    16, //0xC7
    8, //0xC8
    16, //0xC9
    12, //0xCA
    0, //0xCB
    12, //0xCC
    24, //0xCD
    8, //0xCE
    16, //0xCF
    8, //0xD0
    12, //0xD1
    12, //0xD2
    0, //0xD3
    12, //0xD4
    16, //0xD5
    8, //0xD6
    16, //0xD7
    8, //0xD8
    16, //0xD9
    12, //0xDA
    0, //0xDB
    12, //0xDC
    0, //0xDD
    8, //0xDE
    16, //0xDF
    0, //0xE0
    12, //0xE1
    8, //0xE2
    0, //0xE3
    0, //0xE4
    16, //0xE5
    8, //0xE6
    16, //0xE7
    16, //0xE8
    4, //0xE9
    0, //0xEA
    0, //0xEB
    0, //0xEC
    0, //0xED
    8, //0xEE
    16, //0xEF
    0, //0xF0
    12, //0xF1
    8, //0xF2
    4, //0xF3
    0, //0xF4
    16, //0xF5
    8, //0xF6
    16, //0xF7
    12, //0xF8
    8, //0xF9
    0, //0xFA
    4, //0xFB
    0, //0xFC
    0, //0xFD
    8, //0xFE
    16, //0xFF
};

static void (*cb_opcodes[])(uint8_t, GameboyCPU*, Instruction*) = {
    &RLC_0x00, //0x00
    &RLC_0x00, //0x01
    &RLC_0x00, //0x02
    &RLC_0x00, //0x03
    &RLC_0x00, //0x04
    &RLC_0x00, //0x05
    &RLC_0x00, //0x06
    &RLC_0x00, //0x07
    &RRC_0x08, //0x08
    &RRC_0x08, //0x09
    &RRC_0x08, //0x0A
    &RRC_0x08, //0x0B
    &RRC_0x08, //0x0C
    &RRC_0x08, //0x0D
    &RRC_0x08, //0x0E
    &RRC_0x08, //0x0F
    &RL_0x11, //0x10
    &RL_0x11, //0x11
    &RL_0x11, //0x12
    &RL_0x11, //0x13
    &RL_0x11, //0x14
    &RL_0x11, //0x15
    &RL_0x11, //0x16
    &RL_0x11, //0x17
    &RR_0x19, //0x18
    &RR_0x19, //0x19
    &RR_0x19, //0x1A
    &RR_0x19, //0x1B
    &RR_0x19, //0x1C
    &RR_0x19, //0x1D
    &RR_0x19, //0x1E
    &RR_0x19, //0x1F
    &SLA_0x20, //0x20
    &SLA_0x20, //0x21
    &SLA_0x20, //0x22
    &SLA_0x20, //0x23
    &SLA_0x20, //0x24
    &SLA_0x20, //0x25
    &SLA_0x20, //0x26
    &SLA_0x20, //0x27
    &SRA_0x28, //0x28
    &SRA_0x28, //0x29
    &SRA_0x28, //0x2A
    &SRA_0x28, //0x2B
    &SRA_0x28, //0x2C
    &SRA_0x28, //0x2D
    &SRA_0x28, //0x2E
    &SRA_0x28, //0x2F
    &SWAP_0x37, //0x30
    &SWAP_0x37, //0x31
    &SWAP_0x37, //0x32
    &SWAP_0x37, //0x33
    &SWAP_0x37, //0x34
    &SWAP_0x37, //0x35
    &SWAP_0x37, //0x36
    &SWAP_0x37, //0x37
    &SRL_0x38, //0x38
    &SRL_0x38, //0x39
    &SRL_0x38, //0x3A
    &SRL_0x38, //0x3B
    &SRL_0x38, //0x3C
    &SRL_0x38, //0x3D
    &SRL_0x38, //0x3E
    &SRL_0x38, //0x3F
    &BIT_0x7C, //0x40
    &BIT_0x7C, //0x41
    &BIT_0x7C, //0x42
    &BIT_0x7C, //0x43
    &BIT_0x7C, //0x44
    &BIT_0x7C, //0x45
    &BIT_0x7C, //0x46
    &BIT_0x7C, //0x47
    &BIT_0x7C, //0x48
    &BIT_0x7C, //0x49
    &BIT_0x7C, //0x4A
    &BIT_0x7C, //0x4B
    &BIT_0x7C, //0x4C
    &BIT_0x7C, //0x4D
    &BIT_0x7C, //0x4E
    &BIT_0x7C, //0x4F
    &BIT_0x7C, //0x50
    &BIT_0x7C, //0x51
    &BIT_0x7C, //0x52
    &BIT_0x7C, //0x53
    &BIT_0x7C, //0x54
    &BIT_0x7C, //0x55
    &BIT_0x7C, //0x56
    &BIT_0x7C, //0x57
    &BIT_0x7C, //0x58
    &BIT_0x7C, //0x59
    &BIT_0x7C, //0x5A
    &BIT_0x7C, //0x5B
    &BIT_0x7C, //0x5C
    &BIT_0x7C, //0x5D
    &BIT_0x7C, //0x5E
    &BIT_0x7C, //0x5F
    &BIT_0x7C, //0x60
    &BIT_0x7C, //0x61
    &BIT_0x7C, //0x62
    &BIT_0x7C, //0x63
    &BIT_0x7C, //0x64
    &BIT_0x7C, //0x65
    &BIT_0x7C, //0x66
    &BIT_0x7C, //0x67
    &BIT_0x7C, //0x68
    &BIT_0x7C, //0x69
    &BIT_0x7C, //0x6A
    &BIT_0x7C, //0x6B
    &BIT_0x7C, //0x6C
    &BIT_0x7C, //0x6D
    &BIT_0x7C, //0x6E
    &BIT_0x7C, //0x6F
    &BIT_0x7C, //0x70
    &BIT_0x7C, //0x71
    &BIT_0x7C, //0x72
    &BIT_0x7C, //0x73
    &BIT_0x7C, //0x74
    &BIT_0x7C, //0x75
    &BIT_0x7C, //0x76
    &BIT_0x7C, //0x77
    &BIT_0x7C, //0x78
    &BIT_0x7C, //0x79
    &BIT_0x7C, //0x7A
    &BIT_0x7C, //0x7B
    &BIT_0x7C, //0x7C
    &BIT_0x7C, //0x7D
    &BIT_0x7C, //0x7E
    &BIT_0x7C, //0x7F
    &RES_0x87, //0x80
    &RES_0x87, //0x81
    &RES_0x87, //0x82
    &RES_0x87, //0x83
    &RES_0x87, //0x84
    &RES_0x87, //0x85
    &RES_0x87, //0x86
    &RES_0x87, //0x87
    &RES_0x87, //0x88
    &RES_0x87, //0x89
    &RES_0x87, //0x8A
    &RES_0x87, //0x8B
    &RES_0x87, //0x8C
    &RES_0x87, //0x8D
    &RES_0x87, //0x8E
    &RES_0x87, //0x8F
    &RES_0x87, //0x90
    &RES_0x87, //0x91
    &RES_0x87, //0x92
    &RES_0x87, //0x93
    &RES_0x87, //0x94
    &RES_0x87, //0x95
    &RES_0x87, //0x96
    &RES_0x87, //0x97
    &RES_0x87, //0x98
    &RES_0x87, //0x99
    &RES_0x87, //0x9A
    &RES_0x87, //0x9B
    &RES_0x87, //0x9C
    &RES_0x87, //0x9D
    &RES_0x87, //0x9E
    &RES_0x87, //0x9F
    &RES_0x87, //0xA0
    &RES_0x87, //0xA1
    &RES_0x87, //0xA2
    &RES_0x87, //0xA3
    &RES_0x87, //0xA4
    &RES_0x87, //0xA5
    &RES_0x87, //0xA6
    &RES_0x87, //0xA7
    &RES_0x87, //0xA8
    &RES_0x87, //0xA9
    &RES_0x87, //0xAA
    &RES_0x87, //0xAB
    &RES_0x87, //0xAC
    &RES_0x87, //0xAD
    &RES_0x87, //0xAE
    &RES_0x87, //0xAF
    &RES_0x87, //0xB0
    &RES_0x87, //0xB1
    &RES_0x87, //0xB2
    &RES_0x87, //0xB3
    &RES_0x87, //0xB4
    &RES_0x87, //0xB5
    &RES_0x87, //0xB6
    &RES_0x87, //0xB7
    &RES_0x87, //0xB8
    &RES_0x87, //0xB9
    &RES_0x87, //0xBA
    &RES_0x87, //0xBB
    &RES_0x87, //0xBC
    &RES_0x87, //0xBD
    &RES_0x87, //0xBE
    &RES_0x87, //0xBF
    &SET_0xC0, //0xC0
    &SET_0xC0, //0xC1
    &SET_0xC0, //0xC2
    &SET_0xC0, //0xC3
    &SET_0xC0, //0xC4
    &SET_0xC0, //0xC5
    &SET_0xC0, //0xC6
    &SET_0xC0, //0xC7
    &SET_0xC0, //0xC8
    &SET_0xC0, //0xC9
    &SET_0xC0, //0xCA
    &SET_0xC0, //0xCB
    &SET_0xC0, //0xCC
    &SET_0xC0, //0xCD
    &SET_0xC0, //0xCE
    &SET_0xC0, //0xCF
    &SET_0xC0, //0xD0
    &SET_0xC0, //0xD1
    &SET_0xC0, //0xD2
    &SET_0xC0, //0xD3
    &SET_0xC0, //0xD4
    &SET_0xC0, //0xD5
    &SET_0xC0, //0xD6
    &SET_0xC0, //0xD7
    &SET_0xC0, //0xD8
    &SET_0xC0, //0xD9
    &SET_0xC0, //0xDA
    &SET_0xC0, //0xDB
    &SET_0xC0, //0xDC
    &SET_0xC0, //0xDD
    &SET_0xC0, //0xDE
    &SET_0xC0, //0xDF
    &SET_0xC0, //0xE0
    &SET_0xC0, //0xE1
    &SET_0xC0, //0xE2
    &SET_0xC0, //0xE3
    &SET_0xC0, //0xE4
    &SET_0xC0, //0xE5
    &SET_0xC0, //0xE6
    &SET_0xC0, //0xE7
    &SET_0xC0, //0xE8
    &SET_0xC0, //0xE9
    &SET_0xC0, //0xEA
    &SET_0xC0, //0xEB
    &SET_0xC0, //0xEC
    &SET_0xC0, //0xED
    &SET_0xC0, //0xEE
    &SET_0xC0, //0xEF
    &SET_0xC0, //0xF0
    &SET_0xC0, //0xF1
    &SET_0xC0, //0xF2
    &SET_0xC0, //0xF3
    &SET_0xC0, //0xF4
    &SET_0xC0, //0xF5
    &SET_0xC0, //0xF6
    &SET_0xC0, //0xF7
    &SET_0xC0, //0xF8
    &SET_0xC0, //0xF9
    &SET_0xC0, //0xFA
    &SET_0xC0, //0xFB
    &SET_0xC0, //0xFC
    &SET_0xC0, //0xFD
    &SET_0xC0, //0xFE
    &SET_0xC0, //0xFF
};

static int cb_opcode_ticks[] = {
    0, //0x00
    0, //0x01
    0, //0x02
    0, //0x03
    0, //0x04
    0, //0x05
    0, //0x06
    0, //0x07
    0, //0x08
    0, //0x09
    0, //0x0A
    0, //0x0B
    0, //0x0C
    0, //0x0D
    0, //0x0E
    0, //0x0F
    0, //0x10
    0, //0x11
    0, //0x12
    0, //0x13
    0, //0x14
    0, //0x15
    0, //0x16
    0, //0x17
    0, //0x18
    0, //0x19
    0, //0x1A
    0, //0x1B
    0, //0x1C
    0, //0x1D
    0, //0x1E
    0, //0x1F
    0, //0x20
    0, //0x21
    0, //0x22
    0, //0x23
    0, //0x24
    0, //0x25
    0, //0x26
    0, //0x27
    0, //0x28
    0, //0x29
    0, //0x2A
    0, //0x2B
    0, //0x2C
    0, //0x2D
    0, //0x2E
    0, //0x2F
    0, //0x30
    0, //0x31
    0, //0x32
    0, //0x33
    0, //0x34
    0, //0x35
    0, //0x36
    0, //0x37
    0, //0x38
    0, //0x39
    0, //0x3A
    0, //0x3B
    0, //0x3C
    0, //0x3D
    0, //0x3E
    0, //0x3F
    0, //0x40
    0, //0x41
    0, //0x42
    0, //0x43
    0, //0x44
    0, //0x45
    0, //0x46
    0, //0x47
    0, //0x48
    0, //0x49
    0, //0x4A
    0, //0x4B
    0, //0x4C
    0, //0x4D
    0, //0x4E
    0, //0x4F
    0, //0x50
    0, //0x51
    0, //0x52
    0, //0x53
    0, //0x54
    0, //0x55
    0, //0x56
    0, //0x57
    0, //0x58
    0, //0x59
    0, //0x5A
    0, //0x5B
    0, //0x5C
    0, //0x5D
    0, //0x5E
    0, //0x5F
    0, //0x60
    0, //0x61
    0, //0x62
    0, //0x63
    0, //0x64
    0, //0x65
    0, //0x66
    0, //0x67
    0, //0x68
    0, //0x69
    0, //0x6A
    0, //0x6B
    0, //0x6C
    0, //0x6D
    0, //0x6E
    0, //0x6F
    0, //0x70
    0, //0x71
    0, //0x72
    0, //0x73
    0, //0x74
    0, //0x75
    0, //0x76
    0, //0x77
    0, //0x78
    0, //0x79
    0, //0x7A
    0, //0x7B
    0, //0x7C
    0, //0x7D
    0, //0x7E
    0, //0x7F
    0, //0x80
    0, //0x81
    0, //0x82
    0, //0x83
    0, //0x84
    0, //0x85
    0, //0x86
    0, //0x87
    0, //0x88
    0, //0x89
    0, //0x8A
    0, //0x8B
    0, //0x8C
    0, //0x8D
    0, //0x8E
    0, //0x8F
    0, //0x90
    0, //0x91
    0, //0x92
    0, //0x93
    0, //0x94
    0, //0x95
    0, //0x96
    0, //0x97
    0, //0x98
    0, //0x99
    0, //0x9A
    0, //0x9B
    0, //0x9C
    0, //0x9D
    0, //0x9E
    0, //0x9F
    0, //0xA0
    0, //0xA1
    0, //0xA2
    0, //0xA3
    0, //0xA4
    0, //0xA5
    0, //0xA6
    0, //0xA7
    0, //0xA8
    0, //0xA9
    0, //0xAA
    0, //0xAB
    0, //0xAC
    0, //0xAD
    0, //0xAE
    0, //0xAF
    0, //0xB0
    0, //0xB1
    0, //0xB2
    0, //0xB3
    0, //0xB4
    0, //0xB5
    0, //0xB6
    0, //0xB7
    0, //0xB8
    0, //0xB9
    0, //0xBA
    0, //0xBB
    0, //0xBC
    0, //0xBD
    0, //0xBE
    0, //0xBF
    0, //0xC0
    0, //0xC1
    0, //0xC2
    0, //0xC3
    0, //0xC4
    0, //0xC5
    0, //0xC6
    0, //0xC7
    0, //0xC8
    0, //0xC9
    0, //0xCA
    0, //0xCB
    0, //0xCC
    0, //0xCD
    0, //0xCE
    0, //0xCF
    0, //0xD0
    0, //0xD1
    0, //0xD2
    0, //0xD3
    0, //0xD4
    0, //0xD5
    0, //0xD6
    0, //0xD7
    0, //0xD8
    0, //0xD9
    0, //0xDA
    0, //0xDB
    0, //0xDC
    0, //0xDD
    0, //0xDE
    0, //0xDF
    0, //0xE0
    0, //0xE1
    0, //0xE2
    0, //0xE3
    0, //0xE4
    0, //0xE5
    0, //0xE6
    0, //0xE7
    0, //0xE8
    0, //0xE9
    0, //0xEA
    0, //0xEB
    0, //0xEC
    0, //0xED
    0, //0xEE
    0, //0xEF
    0, //0xF0
    0, //0xF1
    0, //0xF2
    0, //0xF3
    0, //0xF4
    0, //0xF5
    0, //0xF6
    0, //0xF7
    0, //0xF8
    0, //0xF9
    0, //0xFA
    0, //0xFB
    0, //0xFC
    0, //0xFD
    0, //0xFE
    0, //0xFF
};

#endif
