/* 338. Counting Bits */

#include <stdlib.h>

int *countBits(int n, int *returnSize)
{
    *returnSize = n + 1;
    int *arr = (int *) malloc((n + 1) * sizeof(int));  // allocate on heap
    if (!arr)
        return NULL;  // check malloc success

    for (int i = 0; i <= n; i++) {
        arr[i] = __builtin_popcount(i);  // or custom bit count function
    }
    return arr;
}
