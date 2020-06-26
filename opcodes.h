#ifndef _OPCODES_H_
#define _OPCODES_H_

#include "gameboy_cpu.h"

extern void LD_0x01x11x21x31(Instruction instruction);
extern void XOR_0xA9(Instruction instruction);
extern void LD_0x32(Instruction instruction);
extern void JR_0x20(Instruction instruction);
extern void LD_0x06(Instruction instruction);
extern void LD_0xE2(Instruction instruction);
extern void LD_0x70(Instruction instruction);
extern void LDH_0xE0(Instruction instruction);
extern void LD_0x1A(Instruction instruction);
extern void INC_0x04x0Cx14x1Cx24x2Cx3C(Instruction instruction);
extern void CALL_0xCD(Instruction instruction);
extern void LD_0x40(Instruction instruction);
extern void LD_0x22(Instruction instruction);
extern void PUSH_0xC5(Instruction instruction);
extern void POP_0xC1(Instruction instruction);
extern void RLA_0x17(Instruction instruction);
extern void DEC_0x05x0Dx15x1Dx25x2Dx3D(Instruction instruction);
extern void INC_0x03x13x23x33(Instruction instruction);
extern void RET_0xC9(Instruction instruction);
extern void CP_0xFE(Instruction instruction);

// CB
extern void BIT_0x7C(Instruction instruction);
extern void RL_0x11(Instruction instruction);

static void (*opcodes[])(Instruction) = {
    nullptr, //0x00
    &LD_0x01x11x21x31, //0x01
    nullptr, //0x02
    &INC_0x03x13x23x33, //0x03
    &INC_0x04x0Cx14x1Cx24x2Cx3C, //0x04
    &DEC_0x05x0Dx15x1Dx25x2Dx3D, //0x05
    &LD_0x06, //0x06
    nullptr, //0x07
    nullptr, //0x08
    nullptr, //0x09
    nullptr, //0x0A
    nullptr, //0x0B
    &INC_0x04x0Cx14x1Cx24x2Cx3C, //0x0C
    &DEC_0x05x0Dx15x1Dx25x2Dx3D, //0x0D
    &LD_0x06, //0x0E
    nullptr, //0x0F
    nullptr, //0x10
    &LD_0x01x11x21x31, //0x11
    nullptr, //0x12
    &INC_0x03x13x23x33, //0x13
    &INC_0x04x0Cx14x1Cx24x2Cx3C, //0x14
    &DEC_0x05x0Dx15x1Dx25x2Dx3D, //0x15
    &LD_0x06, //0x16
    &RLA_0x17, //0x17
    nullptr, //0x18
    nullptr, //0x19
    &LD_0x1A, //0x1A
    nullptr, //0x1B
    &INC_0x04x0Cx14x1Cx24x2Cx3C, //0x1C
    &DEC_0x05x0Dx15x1Dx25x2Dx3D, //0x1D
    &LD_0x06, //0x1E
    nullptr, //0x1F
    &JR_0x20, //0x20
    &LD_0x01x11x21x31, //0x21
    &LD_0x22, //0x22
    &INC_0x03x13x23x33, //0x23
    &INC_0x04x0Cx14x1Cx24x2Cx3C, //0x24
    &DEC_0x05x0Dx15x1Dx25x2Dx3D, //0x25
    &LD_0x06, //0x26
    nullptr, //0x27
    &JR_0x20, //0x28
    nullptr, //0x29
    nullptr, //0x2A
    nullptr, //0x2B
    &INC_0x04x0Cx14x1Cx24x2Cx3C, //0x2C
    &DEC_0x05x0Dx15x1Dx25x2Dx3D, //0x2D
    &LD_0x06, //0x2E
    nullptr, //0x2F
    &JR_0x20, //0x30
    &LD_0x01x11x21x31, //0x31
    &LD_0x32, //0x32
    &INC_0x03x13x23x33, //0x33
    nullptr, //0x34
    nullptr, //0x35
    nullptr, //0x36
    nullptr, //0x37
    &JR_0x20, //0x38
    nullptr, //0x39
    nullptr, //0x3A
    nullptr, //0x3B
    &INC_0x04x0Cx14x1Cx24x2Cx3C, //0x3C
    &DEC_0x05x0Dx15x1Dx25x2Dx3D, //0x3D
    &LD_0x06, //0x3E
    nullptr, //0x3F
    &LD_0x40, //0x40
    &LD_0x40, //0x41
    &LD_0x40, //0x42
    &LD_0x40, //0x43
    &LD_0x40, //0x44
    &LD_0x40, //0x45
    &LD_0x40, //0x46
    &LD_0x40, //0x47
    &LD_0x40, //0x48
    &LD_0x40, //0x49
    &LD_0x40, //0x4A
    &LD_0x40, //0x4B
    &LD_0x40, //0x4C
    &LD_0x40, //0x4D
    nullptr, //0x4E
    &LD_0x40, //0x4F
    &LD_0x40, //0x50
    &LD_0x40, //0x51
    &LD_0x40, //0x52
    &LD_0x40, //0x53
    &LD_0x40, //0x54
    &LD_0x40, //0x55
    &LD_0x40, //0x56
    &LD_0x40, //0x57
    &LD_0x40, //0x58
    &LD_0x40, //0x59
    &LD_0x40, //0x5A
    &LD_0x40, //0x5B
    &LD_0x40, //0x5C
    &LD_0x40, //0x5D
    nullptr, //0x5E
    &LD_0x40, //0x5F
    &LD_0x40, //0x60
    &LD_0x40, //0x61
    &LD_0x40, //0x62
    &LD_0x40, //0x63
    &LD_0x40, //0x64
    &LD_0x40, //0x65
    &LD_0x40, //0x66
    &LD_0x40, //0x67
    &LD_0x40, //0x68
    &LD_0x40, //0x69
    &LD_0x40, //0x6A
    &LD_0x40, //0x6B
    &LD_0x40, //0x6C
    &LD_0x40, //0x6D
    nullptr, //0x6E
    &LD_0x40, //0x6F
    &LD_0x70, //0x70
    &LD_0x70, //0x71
    &LD_0x70, //0x72
    &LD_0x70, //0x73
    &LD_0x70, //0x74
    &LD_0x70, //0x75
    nullptr, //0x76
    &LD_0x70, //0x77
    &LD_0x40, //0x78
    &LD_0x40, //0x79
    &LD_0x40, //0x7A
    &LD_0x40, //0x7B
    &LD_0x40, //0x7C
    &LD_0x40, //0x7D
    nullptr, //0x7E
    &LD_0x40, //0x7F
    nullptr, //0x80
    nullptr, //0x81
    nullptr, //0x82
    nullptr, //0x83
    nullptr, //0x84
    nullptr, //0x85
    nullptr, //0x86
    nullptr, //0x87
    nullptr, //0x88
    nullptr, //0x89
    nullptr, //0x8A
    nullptr, //0x8B
    nullptr, //0x8C
    nullptr, //0x8D
    nullptr, //0x8E
    nullptr, //0x8F
    nullptr, //0x90
    nullptr, //0x91
    nullptr, //0x92
    nullptr, //0x93
    nullptr, //0x94
    nullptr, //0x95
    nullptr, //0x96
    nullptr, //0x97
    nullptr, //0x98
    nullptr, //0x99
    nullptr, //0x9A
    nullptr, //0x9B
    nullptr, //0x9C
    nullptr, //0x9D
    nullptr, //0x9E
    nullptr, //0x9F
    nullptr, //0xA0
    nullptr, //0xA1
    nullptr, //0xA2
    nullptr, //0xA3
    nullptr, //0xA4
    nullptr, //0xA5
    nullptr, //0xA6
    nullptr, //0xA7
    &XOR_0xA9, //0xA8
    &XOR_0xA9, //0xA9
    &XOR_0xA9, //0xAA
    &XOR_0xA9, //0xAB
    &XOR_0xA9, //0xAC
    &XOR_0xA9, //0xAD
    nullptr, //0xAE
    &XOR_0xA9, //0xAF
    nullptr, //0xB0
    nullptr, //0xB1
    nullptr, //0xB2
    nullptr, //0xB3
    nullptr, //0xB4
    nullptr, //0xB5
    nullptr, //0xB6
    nullptr, //0xB7
    nullptr, //0xB8
    nullptr, //0xB9
    nullptr, //0xBA
    nullptr, //0xBB
    nullptr, //0xBC
    nullptr, //0xBD
    nullptr, //0xBE
    nullptr, //0xBF
    nullptr, //0xC0
    &POP_0xC1, //0xC1
    nullptr, //0xC2
    nullptr, //0xC3
    nullptr, //0xC4
    &PUSH_0xC5, //0xC5
    nullptr, //0xC6
    nullptr, //0xC7
    nullptr, //0xC8
    &RET_0xC9, //0xC9
    nullptr, //0xCA
    nullptr, //0xCB
    nullptr, //0xCC
    &CALL_0xCD, //0xCD
    nullptr, //0xCE
    nullptr, //0xCF
    nullptr, //0xD0
    &POP_0xC1, //0xD1
    nullptr, //0xD2
    nullptr, //0xD3
    nullptr, //0xD4
    &PUSH_0xC5, //0xD5
    nullptr, //0xD6
    nullptr, //0xD7
    nullptr, //0xD8
    nullptr, //0xD9
    nullptr, //0xDA
    nullptr, //0xDB
    nullptr, //0xDC
    nullptr, //0xDD
    nullptr, //0xDE
    nullptr, //0xDF
    &LDH_0xE0, //0xE0
    &POP_0xC1, //0xE1
    &LD_0xE2, //0xE2
    nullptr, //0xE3
    nullptr, //0xE4
    &PUSH_0xC5, //0xE5
    nullptr, //0xE6
    nullptr, //0xE7
    nullptr, //0xE8
    nullptr, //0xE9
    nullptr, //0xEA
    nullptr, //0xEB
    nullptr, //0xEC
    nullptr, //0xED
    nullptr, //0xEE
    nullptr, //0xEF
    nullptr, //0xF0
    &POP_0xC1, //0xF1
    nullptr, //0xF2
    nullptr, //0xF3
    nullptr, //0xF4
    &PUSH_0xC5, //0xF5
    nullptr, //0xF6
    nullptr, //0xF7
    nullptr, //0xF8
    nullptr, //0xF9
    nullptr, //0xFA
    nullptr, //0xFB
    nullptr, //0xFC
    nullptr, //0xFD
    &CP_0xFE, //0xFE
    nullptr, //0xFF
};

static int opcode_ticks[] = {
    0, //0x00
    12, //0x01
    0, //0x02
    8, //0x03
    4, //0x04
    4, //0x05
    8, //0x06
    0, //0x07
    0, //0x08
    0, //0x09
    0, //0x0A
    0, //0x0B
    4, //0x0C
    4, //0x0D
    8, //0x0E
    0, //0x0F
    0, //0x10
    12, //0x11
    0, //0x12
    8, //0x13
    4, //0x14
    4, //0x15
    8, //0x16
    4, //0x17
    0, //0x18
    0, //0x19
    8, //0x1A
    0, //0x1B
    4, //0x1C
    4, //0x1D
    8, //0x1E
    0, //0x1F
    8, //0x20
    12, //0x21
    8, //0x22
    8, //0x23
    4, //0x24
    4, //0x25
    8, //0x26
    0, //0x27
    8, //0x28
    0, //0x29
    0, //0x2A
    0, //0x2B
    4, //0x2C
    4, //0x2D
    8, //0x2E
    0, //0x2F
    8, //0x30
    12, //0x31
    8, //0x32
    8, //0x33
    0, //0x34
    0, //0x35
    0, //0x36
    0, //0x37
    8, //0x38
    0, //0x39
    0, //0x3A
    0, //0x3B
    4, //0x3C
    4, //0x3D
    8, //0x3E
    0, //0x3F
    4, //0x40
    4, //0x41
    4, //0x42
    4, //0x43
    4, //0x44
    4, //0x45
    4, //0x46
    4, //0x47
    4, //0x48
    4, //0x49
    4, //0x4A
    4, //0x4B
    4, //0x4C
    4, //0x4D
    0, //0x4E
    4, //0x4F
    4, //0x50
    4, //0x51
    4, //0x52
    4, //0x53
    4, //0x54
    4, //0x55
    4, //0x56
    4, //0x57
    4, //0x58
    4, //0x59
    4, //0x5A
    4, //0x5B
    4, //0x5C
    4, //0x5D
    0, //0x5E
    4, //0x5F
    4, //0x60
    4, //0x61
    4, //0x62
    4, //0x63
    4, //0x64
    4, //0x65
    4, //0x66
    4, //0x67
    4, //0x68
    4, //0x69
    4, //0x6A
    4, //0x6B
    4, //0x6C
    4, //0x6D
    0, //0x6E
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
    0, //0x7E
    4, //0x7F
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
    4, //0xA8
    4, //0xA9
    4, //0xAA
    4, //0xAB
    4, //0xAC
    4, //0xAD
    0, //0xAE
    4, //0xAF
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
    12, //0xC1
    0, //0xC2
    0, //0xC3
    0, //0xC4
    16, //0xC5
    0, //0xC6
    0, //0xC7
    0, //0xC8
    16, //0xC9
    0, //0xCA
    0, //0xCB
    0, //0xCC
    24, //0xCD
    0, //0xCE
    0, //0xCF
    0, //0xD0
    12, //0xD1
    0, //0xD2
    0, //0xD3
    0, //0xD4
    16, //0xD5
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
    12, //0xE1
    8, //0xE2
    0, //0xE3
    0, //0xE4
    16, //0xE5
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
    12, //0xF1
    0, //0xF2
    0, //0xF3
    0, //0xF4
    16, //0xF5
    0, //0xF6
    0, //0xF7
    0, //0xF8
    0, //0xF9
    0, //0xFA
    0, //0xFB
    0, //0xFC
    0, //0xFD
    8, //0xFE
    0, //0xFF
};

static void (*cb_opcodes[])(Instruction) = {
    nullptr, //0x00
    nullptr, //0x01
    nullptr, //0x02
    nullptr, //0x03
    nullptr, //0x04
    nullptr, //0x05
    nullptr, //0x06
    nullptr, //0x07
    nullptr, //0x08
    nullptr, //0x09
    nullptr, //0x0A
    nullptr, //0x0B
    nullptr, //0x0C
    nullptr, //0x0D
    nullptr, //0x0E
    nullptr, //0x0F
    &RL_0x11, //0x10
    &RL_0x11, //0x11
    &RL_0x11, //0x12
    &RL_0x11, //0x13
    &RL_0x11, //0x14
    &RL_0x11, //0x15
    &RL_0x11, //0x16
    &RL_0x11, //0x17
    nullptr, //0x18
    nullptr, //0x19
    nullptr, //0x1A
    nullptr, //0x1B
    nullptr, //0x1C
    nullptr, //0x1D
    nullptr, //0x1E
    nullptr, //0x1F
    nullptr, //0x20
    nullptr, //0x21
    nullptr, //0x22
    nullptr, //0x23
    nullptr, //0x24
    nullptr, //0x25
    nullptr, //0x26
    nullptr, //0x27
    nullptr, //0x28
    nullptr, //0x29
    nullptr, //0x2A
    nullptr, //0x2B
    nullptr, //0x2C
    nullptr, //0x2D
    nullptr, //0x2E
    nullptr, //0x2F
    nullptr, //0x30
    nullptr, //0x31
    nullptr, //0x32
    nullptr, //0x33
    nullptr, //0x34
    nullptr, //0x35
    nullptr, //0x36
    nullptr, //0x37
    nullptr, //0x38
    nullptr, //0x39
    nullptr, //0x3A
    nullptr, //0x3B
    nullptr, //0x3C
    nullptr, //0x3D
    nullptr, //0x3E
    nullptr, //0x3F
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
    nullptr, //0x80
    nullptr, //0x81
    nullptr, //0x82
    nullptr, //0x83
    nullptr, //0x84
    nullptr, //0x85
    nullptr, //0x86
    nullptr, //0x87
    nullptr, //0x88
    nullptr, //0x89
    nullptr, //0x8A
    nullptr, //0x8B
    nullptr, //0x8C
    nullptr, //0x8D
    nullptr, //0x8E
    nullptr, //0x8F
    nullptr, //0x90
    nullptr, //0x91
    nullptr, //0x92
    nullptr, //0x93
    nullptr, //0x94
    nullptr, //0x95
    nullptr, //0x96
    nullptr, //0x97
    nullptr, //0x98
    nullptr, //0x99
    nullptr, //0x9A
    nullptr, //0x9B
    nullptr, //0x9C
    nullptr, //0x9D
    nullptr, //0x9E
    nullptr, //0x9F
    nullptr, //0xA0
    nullptr, //0xA1
    nullptr, //0xA2
    nullptr, //0xA3
    nullptr, //0xA4
    nullptr, //0xA5
    nullptr, //0xA6
    nullptr, //0xA7
    nullptr, //0xA8
    nullptr, //0xA9
    nullptr, //0xAA
    nullptr, //0xAB
    nullptr, //0xAC
    nullptr, //0xAD
    nullptr, //0xAE
    nullptr, //0xAF
    nullptr, //0xB0
    nullptr, //0xB1
    nullptr, //0xB2
    nullptr, //0xB3
    nullptr, //0xB4
    nullptr, //0xB5
    nullptr, //0xB6
    nullptr, //0xB7
    nullptr, //0xB8
    nullptr, //0xB9
    nullptr, //0xBA
    nullptr, //0xBB
    nullptr, //0xBC
    nullptr, //0xBD
    nullptr, //0xBE
    nullptr, //0xBF
    nullptr, //0xC0
    nullptr, //0xC1
    nullptr, //0xC2
    nullptr, //0xC3
    nullptr, //0xC4
    nullptr, //0xC5
    nullptr, //0xC6
    nullptr, //0xC7
    nullptr, //0xC8
    nullptr, //0xC9
    nullptr, //0xCA
    nullptr, //0xCB
    nullptr, //0xCC
    nullptr, //0xCD
    nullptr, //0xCE
    nullptr, //0xCF
    nullptr, //0xD0
    nullptr, //0xD1
    nullptr, //0xD2
    nullptr, //0xD3
    nullptr, //0xD4
    nullptr, //0xD5
    nullptr, //0xD6
    nullptr, //0xD7
    nullptr, //0xD8
    nullptr, //0xD9
    nullptr, //0xDA
    nullptr, //0xDB
    nullptr, //0xDC
    nullptr, //0xDD
    nullptr, //0xDE
    nullptr, //0xDF
    nullptr, //0xE0
    nullptr, //0xE1
    nullptr, //0xE2
    nullptr, //0xE3
    nullptr, //0xE4
    nullptr, //0xE5
    nullptr, //0xE6
    nullptr, //0xE7
    nullptr, //0xE8
    nullptr, //0xE9
    nullptr, //0xEA
    nullptr, //0xEB
    nullptr, //0xEC
    nullptr, //0xED
    nullptr, //0xEE
    nullptr, //0xEF
    nullptr, //0xF0
    nullptr, //0xF1
    nullptr, //0xF2
    nullptr, //0xF3
    nullptr, //0xF4
    nullptr, //0xF5
    nullptr, //0xF6
    nullptr, //0xF7
    nullptr, //0xF8
    nullptr, //0xF9
    nullptr, //0xFA
    nullptr, //0xFB
    nullptr, //0xFC
    nullptr, //0xFD
    nullptr, //0xFE
    nullptr, //0xFF
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
    8, //0x32
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
