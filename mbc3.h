#ifndef _MBC3_H_
#define _MBC3_H_

#include "memory_controller.h"

enum class TimeKey
{
    Second = 0x08,
    Minute = 0x09,
    Hour = 0x0A,
    DayLower = 0x0B,
    DayUpper = 0x0C
};

class Memory;
class MBC3 : public IMemoryController
{
private:
    Memory* memory;
    long rom_bank_number;
    long ram_bank_number;
    bool ram_enabled;

    long clock_register;

    long second;
    long minute;
    long hour;
    long day_lower;
    long day_upper;

    long latch_clock_data;
    long start_millis;
public:
    MBC3(Memory* memory);

    long read(long position) override;
    void write(long position, long value) override;

    void latch_clock();
};

#endif