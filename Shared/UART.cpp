#include "UART.h"

// Define static members
bool UART::transmitting = false;
CircularBuffer<100> UART::inputBuffer;
CircularBuffer<100> UART::outputBuffer;

/**
 * Save the incoming character to the buffer
 */
ISR(UART_RX_vect)
{
    UART::inputBuffer.putChar(UDR);
}

/**
 * ISR Transmit the next character in the buffer if there is one
 * TODO: Make use of the UDRIE UART buffer
 */
ISR(UART_TX_vect)
{
    if (!UART::outputBuffer.isEmpty()) {
        UDR = UART::outputBuffer.getChar();
    }
    else {
        UART::transmitting = false;
    }
}
