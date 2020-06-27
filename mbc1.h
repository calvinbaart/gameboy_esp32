#ifndef _MBC1_H_
#define _MBC1_H_

#include "memory_controller.h"

class Memory;
class MBC1 : public IMemoryController
{
private:
    Memory* memory;
    long rom_bank_number;
    long ram_bank_number;
    bool ram_banking;
    bool ram_enabled;
public:
    MBC1(Memory* memory);

    long read(long position) override;
    void write(long position, long value) override;
};

#endif