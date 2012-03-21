#include "../../Shared/Bit.h"
#include "Sampler.h"
#include "../../Shared/UART.h"

void Sampler::samplePinInput()
{
    static int bitCount = 7;
    static unsigned char data = 0;

    // Get the state of PINB2 and set the appropriate bit in 'value' to it
    bit_write(bit_get(PINB, BIT(PINB2)), data, BIT(bitCount));

    --bitCount;

    if (bitCount < 0) {
        value = data;
        dataReady = true;
        bitCount = 7;
        data = 0;
    }
}

void Sampler::setPinOutput()
{
    static int bitCount = 7;
    static char data = 0;
    static bool parsingData = false;

    // If we are ready to process the next char, fetch it
    if (!parsingData && !UART::inputBuffer.isEmpty()) {
        data = UART::inputBuffer.getChar();
        parsingData = true;
    }

    if (parsingData) {

        // Set the pin to the current state of the bit we read in
        bit_write(bit_get(data, BIT(bitCount)), PORTB, BIT(PINB0));

        --bitCount;

        if (bitCount < 0) {
            bitCount = 7;
            parsingData = false;
        }
    }
}
