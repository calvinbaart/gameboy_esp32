#ifndef _REGISTERS_H_
#define _REGISTERS_H_

struct Registers
{
    uint8_t A;
    uint8_t B;
    uint8_t C;
    uint8_t D;
    uint8_t E;
    uint8_t F;
    uint8_t H;
    uint8_t L;
    uint16_t AF;
    uint16_t SP;
    uint16_t PC;
    uint16_t BC;
    uint16_t DE;
    uint16_t HL;

    uint8_t P1;
    uint8_t SB;
    uint8_t SC;
    uint8_t IF;
    uint8_t IE;
};

#endif
