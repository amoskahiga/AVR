#include "../../Shared/Bit.h"
#include "Sampler.h"
#include "Timer.h"

bool Timer::dataReady = false;
unsigned int Timer::prescaler = 0;
unsigned char Timer::value = 0;

ISR(TIMER0_OVF_vect)
{
    if (Timer::prescaler > 0) {
        --Timer::prescaler;
    }
    else {
        Sampler& sampler = Sampler::getInstance();
        sampler.samplePinInput();
        sampler.setPinOutput();
    }
}
