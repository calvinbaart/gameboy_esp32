#ifndef _REGISTERS_H_
#define _REGISTERS_H_

struct Registers
{
    uint16_t SP;
    uint16_t PC;

    union {
        uint16_t AF;

        struct {
            uint8_t F;
            uint8_t A;
        };
    };

    union {
        uint16_t BC;

        struct {
            uint8_t C;
            uint8_t B;
        };
    };

    union {
        uint16_t DE;

        struct {
            uint8_t E;
            uint8_t D;
        };
    };

    union {
        uint16_t HL;

        struct {
            uint8_t L;
            uint8_t H;
        };
    };

    uint8_t P1;
    uint8_t SB;
    uint8_t SC;
    uint8_t IF;
    uint8_t IE;
};

#endif
