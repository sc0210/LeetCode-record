#include <stdio.h>
#include "stdlib.h"

struct testT {
    int a;
    char c;
};

union testU {
    int a;
    char c;
};

int main()
{
    struct testT aa;
    printf("sizeod(aa)=%d\n", (int) sizeof(aa));

    union testU bb;
    bb.c = 'd';
    printf("sizeod(aa)=%d\n", (int) sizeof(bb));
}