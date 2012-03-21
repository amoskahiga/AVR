#include <avr/cpufunc.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>

#include "LED.h"
#include "Timer.h"
#include "../../Shared/UART.h"

const unsigned int delayDuration = 1000; // In milliseconds

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

    Timer::initialize();
    UART::initalize();

    //Enable Global Interrupts
    sei();
}

int main()
{
    ioinit();

    LED greenLED(&PORTB, &DDRB, PINB0);
    greenLED.toggle(); // For debugging purposes only

    while(true) {
        // Send any byte that has been sampled
        if (Timer::dataReady) {
            //printf("%c", Timer::value);
            Timer::dataReady = false;
        }

        // If we get a byte from the UART, disable the timer for some time
        if (!UART::inputBuffer.isEmpty() && Timer::prescaler == 0) {
            // Delay for some time to allow all the input to come in
            Timer::setWait(1);
        }

        // Get and print all characters in the buffer
//        while (!UART::inputBuffer.isEmpty()) {
//            printf("%c", UART::inputBuffer.getChar());
//        }

        _NOP(); // For some reason this makes it work -- possible compiler bug or memory corruption
    }

    return 0;
}
