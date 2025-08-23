/* 191. Number of 1 Bits */

#include <stdlib.h>

int hammingWeight(int n)
{
    int cnt = 0;

    for (int i = 0; i < 32; i++) {
        if (((uint32_t) n) & (1u << i))
            cnt++;
    }

    return cnt;
}