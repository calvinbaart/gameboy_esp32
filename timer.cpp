#include "timer.h"
#include "gameboy_cpu.h"
#include "memory.h"

Timer* Timer::instance = nullptr;

Timer::Timer(GameboyCPU* cpu)
{
    this->cpu = cpu;

    div = tima = tma = tac = 0;
    div_cycles = timer_cycles = 0;

    cpu->get_memory()->add_register(0xFF07, &read_tac, &write_tac);
    cpu->get_memory()->add_register(0xFF04, &read_div, &write_div);
    cpu->get_memory()->add_register(0xFF05, &read_tima, &write_tima);
    cpu->get_memory()->add_register(0xFF06, &read_tma, &write_tma);

    instance = this;
}

void Timer::tick(long cycles)
{
    div_cycles += cycles;

    while (div_cycles >= 256)
    {
        div_cycles -= 256;
        div = (div + 1) & 0xFF;
    }

    if ((tac & 0x04) == 0) {
        return;
    }

    timer_cycles += cycles;

    long ticksNeeded = 256;
    
    //4096 = per 256 = 1024
    //16384 = per 64 = 256
    //65536 = per 16 = 64
    //262144 = per 4 = 16
    
    switch (tac & 0x03) {
        case 0: //4096 hz
            ticksNeeded = 1024;
            break;
        
        case 3: //16384 hz
            ticksNeeded = 256;
            break;

        case 2: //65536 hz
            ticksNeeded = 64;
            break;

        case 1: //262144 hz
            ticksNeeded = 16;
            break;
    }

    while (timer_cycles >= ticksNeeded)
    {
        timer_cycles -= ticksNeeded;

        if (tima == 0xFF) {
            tima = tma;
            cpu->request_interrupt(Interrupt::TimerInterrupt);
        } else {
            tima++;
        }
    }
}

long Timer::read_tac(long location)
{
    return Timer::instance->tac | 0b11111000;
}

long Timer::read_div(long location)
{
    return Timer::instance->div;
}

long Timer::read_tima(long location)
{
    return Timer::instance->tima;
}

long Timer::read_tma(long location)
{
    return Timer::instance->tma;
}

void Timer::write_tac(long location, long data)
{
    Timer::instance->tac = data & 0xFF;
}

void Timer::write_div(long location, long data)
{
    Timer::instance->div = 0;
}

void Timer::write_tima(long location, long data)
{
    Timer::instance->tima = data & 0xFF;
}

void Timer::write_tma(long location, long data)
{
    Timer::instance->tma = data & 0xFF;
}