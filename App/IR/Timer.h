#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>
#include <avr/interrupt.h>

#include "../../Shared/Bit.h"

class Timer
{
public:

    enum Speed
    {
        Fast,   // 14456_overflows/sec
        Slow    // 14_overflow/sec
    } speed;

    static Timer& getInstance()
    {
        static Timer instance;
        return instance;
    }

    void enable(Speed newSpeed)
    {
        // Disable Timer0 overflow interrupt
        bit_clear(TIMSK, BIT(TOIE0));

        // Setup the timer starting value
        TCNT0 = 0;

        speed = newSpeed;

        if (speed == Fast) {
            // Setup the Timer0 prescaler = FCPU/1
            // @3.6864 MHz, this will be (3686400 / 255 / 1) = 14456_overflows/sec
            bit_set(TCCR0, BIT(CS00));
            bit_clear(TCCR0, BIT(CS02));
        }
        else
        {
            // @3.6864 MHz, this will be (3686400 / 255 / 1024) = 14_overflows/sec
            bit_set(TCCR0, BIT(CS00));
            bit_set(TCCR0, BIT(CS02));
        }

        // Enable Timer0 overflow interrupt
        bit_set(TIMSK, BIT(TOIE0));
    }
};

#endif // TIMER_H
