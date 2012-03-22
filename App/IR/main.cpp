#include <avr/cpufunc.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>

#include "LED.h"
#include "Timer.h"
#include "Sampler.h"
#include "../../Shared/UART.h"

const unsigned int delayDuration = 1000; // In milliseconds

Timer& timer = Timer::getInstance();
Sampler& sampler = Sampler::getInstance();

/*
 * Do all the startup-time peripheral initializations.
 */
static void ioinit(void)
{
    wdt_disable();

    // Set all pins as input (high impedance)
    DDRA = 0x00;
    DDRB = 0x00;
    DDRC = 0x00;
    DDRD = 0x00;
    DDRE = 0x00;

    timer.enable(Timer::Fast);
    UART::initalize(UART::BAUD_9600);

    //Enable Global Interrupts
    sei();
}

int main()
{
    ioinit();

    sampler.processingInput = false;

    LED greenLED(&PORTB, &DDRB, PINB0);
    greenLED.toggle(); // For debugging purposes only

    while(true) {
        // Send any byte that has been sampled
        if (sampler.dataReady) {
            //printf("%c", Timer::value);
            sampler.dataReady = false;
        }

        /* If we get a byte from the UART (and are not in the middle of processing old data),
         * slow the timer for some time to prevent its interrupt from starving the UART interrupt.
         */
        if (!UART::inputBuffer.isEmpty() && !sampler.processingInput) {
            // Delay for some time to allow all the input to come in
            timer.enable(Timer::Slow);
            sampler.processingInput = true;
        }

//        // Get and print all characters in the buffer
//        while (!UART::inputBuffer.isEmpty()) {
//            printf("%c", UART::inputBuffer.getChar());
//        }

        _NOP(); // For some reason this makes it work -- possible compiler bug or memory corruption
    }

    return 0;
}
