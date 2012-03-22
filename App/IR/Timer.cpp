#include "../../Shared/Bit.h"
#include "Sampler.h"
#include "Timer.h"

ISR(TIMER0_OVF_vect)
{
    const unsigned int MAX_PRESCALER = 14;
    static unsigned int prescaler = MAX_PRESCALER;

    Timer& timer = Timer::getInstance();
    Sampler& sampler = Sampler::getInstance();

    if (timer.speed == Timer::Fast) {

        sampler.samplePinInput();
        sampler.setPinOutput();
    }
    else {  // In Slow mode

        if (prescaler > 0) {
            --prescaler;
        }

        if (prescaler == 0) {
            // Re-enable the fast timer
            prescaler = MAX_PRESCALER;
            timer.enable(Timer::Fast);
        }
    }
}
