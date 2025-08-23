/* 190. Reverse Bits */

#include <stdint.h>

int reverseBits(int n)
{
    uint32_t res = 0;
    for (int i = 0; i < 32; i++) {
        if (n & (1u << (31 - i))) {  // use unsigned shift
            res |= (1u << i);
        }
    }
    return res;
}