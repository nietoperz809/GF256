//#include <stdint.h>
#include <stdio.h>

/* Add two numbers in a GF(2^8) finite field */
uint8_t gadd(uint8_t a, uint8_t b) {
	return a ^ b;
}

/* Subtract two numbers in a GF(2^8) finite field */
uint8_t gsub(uint8_t a, uint8_t b) {
	return a ^ b;
}

/* Multiply two numbers in the GF(2^8) finite field defined
 * by the polynomial x^8 + x^4 + x^3 + x + 1 = 0
 * using the Russian Peasant Multiplication algorithm
 * (the other way being to do carry-less multiplication followed by a modular reduction)
 */
uint8_t gmul(uint8_t a, uint8_t b) {
	uint8_t p = 0; /* the product of the multiplication */
	while (b) {
            if (b & 1) /* if b is odd, then add the corresponding a to p (final product = sum of all a's corresponding to odd b's) */
                p ^= a; /* since we're in GF(2^m), addition is an XOR */

            if (a & 0x80) /* GF modulo: if a >= 128, then it will overflow when shifted left, so reduce */
                a = (a << 1) ^ 0x11b; /* XOR with the primitive polynomial x^8 + x^4 + x^3 + x + 1 (0b1_0001_1011) – you can change it but it must be irreducible */
            else
                a <<= 1; /* equivalent to a*2 */
            b >>= 1; /* equivalent to b // 2 */
	}
	return p;
}

int main()
{
    uint8_t a = 11;
    uint8_t b = 21;
    uint8_t c = gmul (a,b);
    printf ("%d", c);
    return 0;
}
