#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>
#include <avr/interrupt.h>

class Timer
{

public:

    static bool dataReady;
    static unsigned char value;
    static unsigned int prescaler;

    static void initialize()
    {
        // Setup the Timer0 prescaler = FCPU/1
        // @3.6864 MHz, this will be (3686400 / 255 / 1) = 14456_overflows/sec
        TCCR0 = (1 << CS00);

        // Setup the timer starting value
        TCNT0 = 0;

        // Enable Timer0 overflow interrupt
        TIMSK |= (1 << TOIE0);
    }
    static void setWait(unsigned long duration_sec)
    {
        prescaler = 14456 * duration_sec;
    }
};

#endif // TIMER_H
