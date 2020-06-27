#ifndef _TIMER_H_
#define _TIMER_H_

#include "board_config.h"

class GameboyCPU;
class Timer
{
private:
    GameboyCPU* cpu;

    long div;
    long tima;
    long tma;
    long tac;

    long div_cycles;
    long timer_cycles;

    static long read_tac(long location);
    static long read_div(long location);
    static long read_tima(long location);
    static long read_tma(long location);

    static void write_tac(long location, long data);
    static void write_div(long location, long data);
    static void write_tima(long location, long data);
    static void write_tma(long location, long data);
public:
    Timer(GameboyCPU* cpu);

    void tick(long cycles);

    static Timer* instance;
};

#endif