#ifndef UART_H
#define UART_H

#include <avr/interrupt.h>
#include <stdio.h>

#include "CircularBuffer.h"

class UART
{
public:

    static bool transmitting;
    static CircularBuffer<100> inputBuffer;
    static CircularBuffer<100> outputBuffer;

    enum BaudRate
    {
        BAUD_1200 = 1200,
        BAUD_2400 = 2400,
        BAUD_4800 = 4800,
        BAUD_9600 = 9600,
        BAUD_14400 = 14400,
        BAUD_19200 = 19200,
        BAUD_28800 = 28800,
        BAUD_38400 = 38400,
        BAUD_57600 = 57600,
        BAUD_76800 = 76800,
        BAUD_115200 = 115200,
        BAUD_230400 = 230400
    };

    inline static void initalize(BaudRate baudRate = BAUD_115200)
    {
        // Turn on the transmission and reception circuitry
        UCSRB |= (1 << RXEN) | (1 << TXEN) ;

        // Use 8 bit character sizes, 1 stop bit, no parity, no flow control (asynchronous)
        UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);

        // Compute the baud rate prescale
        const unsigned int preScale = (((unsigned long)F_CPU / (baudRate * 16UL))) - 1;

        // Load upper 8 - bits of the baud rate value into the high byte of the UBRR register
        UBRRH = (unsigned char)(preScale >> 8);

        // Load lower 8 - bits of the baud rate value into the low byte of the UBRR register
        UBRRL = (unsigned char)preScale;

        // Enable the UART Recieve and Transmit Complete interrupts
        UCSRB |= (1 << RXCIE) | (1 << TXCIE);

        // Connect the printf stream to stdio
        FILE m_stdout;
        fdev_setup_stream(&m_stdout, UART::putChar, UART::getChar, _FDEV_SETUP_RW);
        stdout = &m_stdout; //Required for printf init
    }

    /**
     * Get a character from our circular buffer, or return _FDEV_EOF if none was found
     */
    static int getChar(FILE* stream = NULL)
    {
        if (!inputBuffer.isEmpty()) {
            return inputBuffer.getChar();
        }
        else {
            return _FDEV_EOF;
        }
    }

    /**
     * Append a character into our circular buffer, to be sent later
     */
    static int putChar(char c, FILE* stream = NULL)
    {
        outputBuffer.putChar(c);

        // Start the transmission if not already started
        if (!transmitting) {
            transmitting = true;
            UDR = outputBuffer.getChar();   // TODO: We can add a conditional check to directly transmit 'c'
        }
        return 0;
    }
};


#endif // UART_H
