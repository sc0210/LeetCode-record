#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Problem 1: Pointer Arithmetic and Arrays
void problem1()
{
    printf("=== Problem 1: Pointer Arithmetic ===\n");
    int arr[] = {10, 20, 30, 40, 50};
    int *ptr = arr;

    printf("*ptr = %d\n", *ptr);              // 10
    printf("*(ptr + 2) = %d\n", *(ptr + 2));  // 30
    printf("*++ptr = %d\n", *++ptr);          // 20
    printf("*ptr++ = %d\n", *ptr++);          // 20
    printf("*ptr = %d\n", *ptr);              // 30
    printf("\n");
}

// Problem 2: Memory Management
void problem2()
{
    printf("=== Problem 2: Memory Management ===\n");
    int *p = (int *) malloc(5 * sizeof(int));

    for (int i = 0; i < 5; i++) {
        p[i] = i * 2;
    }

    printf("Array contents: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", *(p + i));  // 0,2,4,6,8
    }
    printf("\n");

    free(p);
    // What happens if we try to access p after free?
    // printf("After free: %d\n", *p); // Undefined behavior!
    printf("\n");
}

// Problem 3: Bit Manipulation
void problem3()
{
    printf("=== Problem 3: Bit Manipulation ===\n");
    unsigned char x = 0x5A;  // 01011010 in binary

    printf("x = 0x%02X (binary: ", x);
    for (int i = 7; i >= 0; i--) {
        printf("%d", (x >> i) & 1);
    }
    printf(")\n");

    printf("x << 2 = 0x%02X\n", x << 2);
    printf("x >> 3 = 0x%02X\n", x >> 3);
    printf("x & 0x0F = 0x%02X\n", x & 0x0F);
    printf("x | 0x80 = 0x%02X\n", x | 0x80);
    printf("~x = 0x%02X\n", (unsigned char) ~x);
    printf("\n");
}

// Problem 4: String Manipulation
void problem4()
{
    printf("=== Problem 4: String Manipulation ===\n");
    char str1[20] = "Hello";
    char str2[] = " World";
    char *str3 = "Test";

    printf("str1: %s\n", str1);
    strcat(str1, str2);
    printf("After strcat: %s\n", str1);
    printf("Length: %zu\n", strlen(str1));

    // What's the difference between these?
    char *p1 = "Static";
    char p2[] = "Dynamic";
    printf("p1 points to: %s\n", p1);
    printf("p2 contains: %s\n", p2);
    printf("\n");
}

// Problem 5: Function Pointers
int add(int a, int b)
{
    return a + b;
}
int multiply(int a, int b)
{
    return a * b;
}

void problem5()
{
    printf("=== Problem 5: Function Pointers ===\n");
    int (*operation)(int, int);

    operation = add;
    printf("5 + 3 = %d\n", operation(5, 3));

    operation = multiply;
    printf("5 * 3 = %d\n", operation(5, 3));

    // Array of function pointers
    int (*ops[])(int, int) = {add, multiply};
    printf("Using array: 4 + 6 = %d\n", ops[0](4, 6));
    printf("Using array: 4 * 6 = %d\n", ops[1](4, 6));
    printf("\n");
}

// Problem 6: Structures and Unions
typedef struct {
    int x;
    int y;
} Point;

typedef union {
    int i;
    float f;
    char bytes[4];
} DataUnion;

void problem6()
{
    printf("=== Problem 6: Structures and Unions ===\n");
    Point p = {10, 20};
    printf("Point: (%d, %d)\n", p.x, p.y);
    printf("Size of Point: %zu bytes\n", sizeof(Point));

    DataUnion data;
    data.i = 0x12345678;
    printf("As int: 0x%08X\n", data.i);
    printf("As float: %f\n", data.f);
    printf("As bytes: 0x%02X 0x%02X 0x%02X 0x%02X\n", data.bytes[0],
           data.bytes[1], data.bytes[2], data.bytes[3]);
    printf("\n");
}

// Problem 7: Volatile and const
void problem7()
{
    printf("=== Problem 7: Volatile and Const ===\n");
    volatile int sensor_value = 100;
    const int max_temp = 85;

    printf("Sensor: %d, Max: %d\n", sensor_value, max_temp);

    // sensor_value can change unexpectedly (hardware register)
    // max_temp = 90; // This would cause a compiler error

    const char *str1 = "Hello";  // Can't modify string, can modify pointer
    char const *str2 = "World";  // Same as above
    char *const str3 = "Fixed";  // Can't modify pointer, can modify string
    // const char *const str4 = "Both"; // Can't modify either

    printf("str1: %s, str2: %s, str3: %s\n", str1, str2, str3);
    printf("\n");
}

// Problem 8: Preprocessor and Macros
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define SQUARE(x) ((x) * (x))
#define PRINT_VAR(var) printf(#var " = %d\n", var)

void problem8()
{
    printf("=== Problem 8: Preprocessor ===\n");
    int a = 5, b = 8;

    printf("MAX(%d, %d) = %d\n", a, b, MAX(a, b));
    printf("SQUARE(%d) = %d\n", a, SQUARE(a));

    PRINT_VAR(a);
    PRINT_VAR(b);

    // Watch out for side effects!
    int c = 3;
    printf("SQUARE(++c) = %d, c = %d\n", SQUARE(++c), c);  // 16, 5
    printf("\n");
}

int main()
{
    printf("C Interview Practice Problems\n");
    printf("=============================\n\n");

    problem1();
    problem2();
    problem3();
    problem4();
    problem5();
    problem6();
    problem7();
    problem8();

    printf("Try to predict the output before running!\n");
    return 0;
}