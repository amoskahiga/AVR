#ifndef SAMPLER_H
#define SAMPLER_H

#include <avr/io.h>
#include <avr/interrupt.h>

class Sampler
{

public:

    bool dataReady;
    unsigned char value;

    void samplePinInput();
    void setPinOutput();

    static Sampler& getInstance()
    {
        static Sampler instance;
        return instance;
    }
};

#endif // SAMPLER_H
