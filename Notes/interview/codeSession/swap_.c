#include "stdio.h"

void swap(int *, int *);
void swapFake(int, int);
void swapAddr(int *, int *);

int main()
{
    printf("void swap(int *, int *);\n");
    int a = 10, b = 20;
    printf("Before swap a=%d, b=%d\n", a, b);
    swap(&a, &b);
    printf("After swap a=%d, b=%d\n\n", a, b);

    printf("void swapFake(int, int);\n");
    a = 10, b = 20;
    printf("Before swap a=%d, b=%d\n", a, b);
    swapFake(a, b);
    printf("After swap a=%d, b=%d\n\n", a, b);

    printf("void swapAddr(int *, int *);\n");
    a = 10, b = 20;
    printf("Before swap a=%d, b=%d\n", a, b);
    swapAddr(&a, &b);
    printf("After swap a=%d, b=%d\n\n", a, b);

    return 0;
}


void swap(int *ptrA, int *ptrB)
{
    int tmp = *ptrA;
    *ptrA = *ptrB;
    *ptrB = tmp;
};

void swapFake(int a, int b)
{
    int tmp = a;
    a = b;
    b = tmp;
};


void swapAddr(int *ptrA, int *ptrB)
{
    int *tmp = ptrA;
    ptrA = ptrB;
    ptrB = tmp;
};
