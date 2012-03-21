#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#include <stddef.h>

template <size_t SIZE>
class CircularBuffer{

public:
    CircularBuffer() :
        m_end(0),
        m_start(0)
    {
    }

    bool isFull()
    {
        return (m_end + 1) % SIZE == m_start;
    }

    // Check if the buffer has data. We must check this BEFORE using get().
    int isEmpty()
    {
        return m_end == m_start;
    }

    // Get the number of bytes currently held by the buffer
    unsigned int size()
    {
        return m_end - m_start;
    }

    /* Write an element, overwriting oldest element if buffer is full.
     * App can choose to avoid the overwrite by checking isFull().
     */
    void putChar(char c)
    {
        m_buffer[m_end] = c;
        m_end = (m_end + 1) % SIZE;

         // If we were previously full, we overwrote the first item and therefore need to skip over it
        if (m_end == m_start) {
            m_start = (m_start + 1) % SIZE;
        }
    }

    // Read oldest element. App MUST ensure !isEmpty() first.
    char getChar()
    {
        char c = m_buffer[m_start];
        m_start = (m_start + 1) % SIZE;
        return c;
    }

private:
    unsigned int m_end;
    unsigned int m_start;
    char m_buffer[SIZE];
};

#endif // CIRCULARBUFFER_H
