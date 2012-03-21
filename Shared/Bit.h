#ifndef BIT_H
#define BIT_H

/**
 * Bit manipulation helper macros
 *
 * Based on Eric Weddington post at: http://www.avrfreaks.net/index.php?name=PNphpBB2&file=viewtopic&p=40351
 *
 * Note: Bits positions start at a 0 index
 *
 * Examples:
 * bit_set(PORTA, 0x08);  // Set the 4th bit of PORTA
 * bit_set(PORTA, BIT(2) | BIT(4));   // Set bit 2 (the third bit) and 4 (the fifth bit) of PORTA
 * bit_clear(PORTA, 0x40);    // Set the 4th bit of PORTA
 * bit_flip(PORTA, BIT(0));   // Flip bit number 0:
 * bit_get(PINA, BIT(2));    // Get bit 2 (third bit) of PORTA. Note: We use PINX to obtain the current value
 * bit_write(bit_get(PINA, BIT(PINA4)), PORTB, BIT(PINB3));   // Set PORTB3 with the value of PINA4
 */

#define BIT(x) (0x01 << (x))    // Get a int with only the defined bit set (1)
#define LONGBIT(x) ((unsigned long)0x00000001 << (x)) // Get a 16-bit long with only the defined bit set (1)

#define bit_get(p,m) ((p) & (m))
#define bit_set(p,m) ((p) |= (m))
#define bit_clear(p,m) ((p) &= ~(m))
#define bit_flip(p,m) ((p) ^= (m))
#define bit_write(c,p,m) (c ? bit_set(p,m) : bit_clear(p,m))
#define GET_BITS(num, from, to) (((num) >> (from)) & ((0x1 << ((to) - (from) + 1)) - 1))

#endif // BIT_H
