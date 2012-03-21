#ifndef LED_H
#define LED_H

/**
 * Class representing an LED connected to one of the I/O port pins
 */
class LED
{
public:

    /**
     * Constructor
     * @param port
     * @param ddr
     * @param enabled
     */
    LED(volatile uint8_t* port, volatile uint8_t* ddr, uint8_t pinNumber, bool enabled = false) :
        m_port(port),
        m_ddr(ddr),
        m_pinNumber(pinNumber)
    {
        // Set the pin as an output pin by setting(1) its data direction register
        *m_ddr |= _BV(m_pinNumber);

        // Set the default pin state
        if (enabled) {
            *m_port |= _BV(m_pinNumber);   // ON
        }
        else {
            *m_port &= ~_BV(m_pinNumber);   // OFF
        }
    }

    // Toggle the LED ON or OFF based on the previous state
    void toggle() {
        *m_port = *m_port ^ (m_pinNumber + 1);
    }

private:
    volatile uint8_t* m_port;
    volatile uint8_t* m_ddr;
    const uint8_t m_pinNumber;
};

#endif // LED_H
