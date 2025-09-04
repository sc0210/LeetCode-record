#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Problem 9: Tricky Pointer Declarations
void problem9()
{
    printf("=== Problem 9: Complex Pointer Declarations ===\n");

    int x = 42;
    int *p1 = &x;          // Pointer to int
    int **p2 = &p1;        // Pointer to pointer to int
    int *arr[3];           // Array of pointers to int
    int (*ptr_to_arr)[3];  // Pointer to array of 3 ints

    printf("x = %d\n", x);        // 42
    printf("*p1 = %d\n", *p1);    // 42
    printf("**p2 = %d\n", **p2);  // 42

    // What's the difference?
    printf("Size of arr: %zu\n", sizeof(arr));                // 24
    printf("Size of ptr_to_arr: %zu\n", sizeof(ptr_to_arr));  // 8
    printf("\n");
}

// Problem 10: Endianness Check
void problem10()
{
    printf("=== Problem 10: Endianness Detection ===\n");

    union {
        uint32_t i;
        uint8_t c[4];
    } test;

    test.i = 0x12345678;

    printf("32-bit value: 0x%08X\n", test.i);
    printf("Byte order: 0x%02X 0x%02X 0x%02X 0x%02X\n", test.c[0], test.c[1],
           test.c[2], test.c[3]);

    if (test.c[0] == 0x78) {
        printf("System is: Little Endian\n");
    } else {
        printf("System is: Big Endian\n");
    }
    printf("\n");
}

// Problem 11: Stack vs Heap
char *getString1()
{
    char str[] = "Hello";  // Local array on stack
    return str;            // Returning address of local variable!
}

char *getString2()
{
    static char str[] = "Hello";  // Static storage
    return str;                   // Safe to return
}

char *getString3()
{
    char *str = malloc(6);  // Heap allocation
    strcpy(str, "Hello");
    return str;  // Safe, but caller must free()
}

void problem11()
{
    printf("=== Problem 11: Stack vs Heap Memory ===\n");

    // char *s1 = getString1();  // DANGEROUS! Undefined behavior
    char *s2 = getString2();  // Safe
    char *s3 = getString3();  // Safe but needs free()

    printf("getString2(): %s\n", s2);
    printf("getString3(): %s\n", s3);

    free(s3);  // Don't forget this!
    printf("\n");
}

// Problem 12: Structure Padding and Alignment
struct BadStruct {
    char a;    // 1 byte
    int b;     // 4 bytes (likely padded)
    char c;    // 1 byte
    double d;  // 8 bytes (likely padded)
};

struct GoodStruct {
    double d;  // 8 bytes
    int b;     // 4 bytes
    char a;    // 1 byte
    char c;    // 1 byte
    // 2 bytes padding at end
};

void problem12()
{
    printf("=== Problem 12: Structure Padding ===\n");

    printf("Size of BadStruct: %zu bytes\n", sizeof(struct BadStruct));
    printf("Size of GoodStruct: %zu bytes\n", sizeof(struct GoodStruct));
    printf("Size of char: %zu\n", sizeof(char));
    printf("Size of int: %zu\n", sizeof(int));
    printf("Size of double: %zu\n", sizeof(double));
    printf("\n");
}

// Problem 13: Function Pointer Arrays (Firmware State Machine)
typedef enum {
    STATE_IDLE,
    STATE_RUNNING,
    STATE_ERROR,
    STATE_MAX
} system_state_t;

void handle_idle()
{
    printf("Handling IDLE state\n");
}
void handle_running()
{
    printf("Handling RUNNING state\n");
}
void handle_error()
{
    printf("Handling ERROR state\n");
}

void problem13()
{
    printf("=== Problem 13: State Machine with Function Pointers ===\n");

    void (*state_handlers[])(void) = {handle_idle, handle_running,
                                      handle_error};

    system_state_t current_state = STATE_RUNNING;

    if (current_state < STATE_MAX) {
        state_handlers[current_state]();
    }
    printf("\n");
}

// Problem 14: Bit Fields (Hardware Registers)
struct StatusRegister {
    unsigned int ready : 1;      // Bit 0
    unsigned int error : 1;      // Bit 1
    unsigned int mode : 2;       // Bits 2-3
    unsigned int reserved : 4;   // Bits 4-7
    unsigned int device_id : 8;  // Bits 8-15
    unsigned int version : 16;   // Bits 16-31
};

void problem14()
{
    printf("=== Problem 14: Bit Fields (Hardware Registers) ===\n");

    struct StatusRegister reg;
    reg.ready = 1;
    reg.error = 0;
    reg.mode = 2;  // 10 in binary
    reg.reserved = 0;
    reg.device_id = 0xAB;
    reg.version = 0x1234;

    printf("Size of StatusRegister: %zu bytes\n",
           sizeof(struct StatusRegister));
    printf("Ready: %u, Error: %u, Mode: %u\n", reg.ready, reg.error, reg.mode);
    printf("Device ID: 0x%02X, Version: 0x%04X\n", reg.device_id, reg.version);

    // Access as raw 32-bit value (careful with portability!)
    uint32_t *raw = (uint32_t *) &reg;
    printf("Raw register value: 0x%08X\n", *raw);
    printf("\n");
}

// Problem 15: Memory Alignment and Packing
struct UnpackedStruct {
    char a;
    int b;
    char c;
};

#pragma pack(1)  // Force byte alignment
struct PackedStruct {
    char a;
    int b;
    char c;
};
#pragma pack()  // Reset to default alignment

void problem15()
{
    printf("=== Problem 15: Packed vs Unpacked Structures ===\n");

    printf("UnpackedStruct size: %zu bytes\n", sizeof(struct UnpackedStruct));
    printf("PackedStruct size: %zu bytes\n", sizeof(struct PackedStruct));

    struct UnpackedStruct u = {'A', 0x12345678, 'B'};
    struct PackedStruct p = {'A', 0x12345678, 'B'};

    printf("Unpacked: a=%c, b=0x%X, c=%c\n", u.a, u.b, u.c);
    printf("Packed: a=%c, b=0x%X, c=%c\n", p.a, p.b, p.c);
    printf("\n");
}

// Problem 16: Circular Buffer (Common in Embedded Systems)
#define BUFFER_SIZE 8

typedef struct {
    int buffer[BUFFER_SIZE];
    int head;
    int tail;
    int count;
} CircularBuffer;

void cb_init(CircularBuffer *cb)
{
    cb->head = cb->tail = cb->count = 0;
}

int cb_put(CircularBuffer *cb, int data)
{
    if (cb->count >= BUFFER_SIZE) {
        return -1;  // Buffer full
    }
    cb->buffer[cb->head] = data;
    cb->head = (cb->head + 1) % BUFFER_SIZE;
    cb->count++;
    return 0;
}

int cb_get(CircularBuffer *cb, int *data)
{
    if (cb->count == 0) {
        return -1;  // Buffer empty
    }
    *data = cb->buffer[cb->tail];
    cb->tail = (cb->tail + 1) % BUFFER_SIZE;
    cb->count--;
    return 0;
}

void problem16()
{
    printf("=== Problem 16: Circular Buffer ===\n");

    CircularBuffer cb;
    cb_init(&cb);

    // Fill buffer
    for (int i = 0; i < 10; i++) {
        if (cb_put(&cb, i * 10) == 0) {
            printf("Added: %d\n", i * 10);
        } else {
            printf("Buffer full, couldn't add: %d\n", i * 10);
        }
    }

    // Empty buffer
    int data;
    while (cb_get(&cb, &data) == 0) {
        printf("Retrieved: %d\n", data);
    }
    printf("\n");
}

// Problem 17: Undefined Behavior Examples
void problem17()
{
    printf("=== Problem 17: Undefined Behavior Traps ===\n");

    // 1. Signed integer overflow
    int max_int = 2147483647;  // Assuming 32-bit int
    printf("max_int = %d\n", max_int);
    printf("max_int + 1 = %d (undefined behavior!)\n", max_int + 1);

    // 2. Array bounds
    int arr[5] = {1, 2, 3, 4, 5};
    printf("arr[4] = %d (valid)\n", arr[4]);
    printf("arr[5] = %d (undefined behavior!)\n", arr[5]);

    // 3. Null pointer dereference
    int *null_ptr = NULL;
    // printf("*null_ptr = %d\n", *null_ptr);  // Would crash!

    printf("Always check pointers before dereferencing!\n");
    printf("\n");
}

// Problem 18: Interrupt Simulation (Firmware Concept)
volatile int interrupt_flag = 0;
volatile int counter = 0;

// Simulates an interrupt service routine
void simulate_interrupt()
{
    interrupt_flag = 1;
    counter++;
}

void problem18()
{
    printf("=== Problem 18: Interrupt Handling Concept ===\n");

    printf("Initial: flag=%d, counter=%d\n", interrupt_flag, counter);

    // Simulate main loop checking for interrupt
    for (int i = 0; i < 3; i++) {
        simulate_interrupt();  // Simulate interrupt occurring

        // Main loop checking interrupt flag
        if (interrupt_flag) {
            printf("Interrupt handled! Counter: %d\n", counter);
            interrupt_flag = 0;  // Clear flag
        }
    }
    printf("\n");
}

int main()
{
    printf("Advanced C Interview Problems\n");
    printf("============================\n\n");

    problem9();
    problem10();
    problem11();
    problem12();
    problem13();
    problem14();
    problem15();
    problem16();
    problem17();
    problem18();

    printf("Challenge Questions:\n");
    printf("1. Why is 'volatile' important in interrupt handlers?\n");
    printf("2. When would you use packed structures?\n");
    printf("3. How does endianness affect network protocols?\n");
    printf("4. What's the difference between malloc() and calloc()?\n");
    printf("5. Why might you avoid recursion in embedded systems?\n");

    return 0;
}