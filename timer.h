#ifndef _TIMER_H_
#define _TIMER_H_

#include "board_config.h"

class GameboyCPU;
class Timer
{
private:
    GameboyCPU* cpu;
public:
    Timer(GameboyCPU* cpu);

    void tick(long cycles);

    static Timer* instance;

    long div;
    long tima;
    long tma;
    long tac;

    long div_cycles;
    long timer_cycles;
};

#endif
