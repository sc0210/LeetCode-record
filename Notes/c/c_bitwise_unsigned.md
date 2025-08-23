
# ✅ C/C++ Bitwise Operations and `unsigned` Usage Guide

## 1. Why Use `unsigned` for Bitwise Operations?

Bitwise operations in C and C++ are tricky when applied to **signed integers**, because:
- **Signed Left Shift (`<<`) UB**  
  If a shift causes a sign bit change or overflow, it's **undefined behavior** for signed integers.

  ```cpp
  int x = 1 << 31; // ❌ Undefined if int is 32-bit
  ```

- **Signed Right Shift (`>>`) Implementation-Defined**  
  For negative numbers, result may be:
    - **Arithmetic shift** (preserve sign) → common on most compilers
    - **Logical shift** (fill with zeros) → some compilers/platforms

- **Unsigned Behavior is Well-Defined**  
  `unsigned` guarantees:
    - Left shift fills with 0
    - Right shift fills with 0 (logical shift)
    - Overflow wraps around (mod 2^n)

---

## 2. Common Mistakes and Correct Usage

### 2.1 Reverse Bits Example
```cpp
int reverseBits(int n) {
    uint32_t res = 0;
    for (int i = 0; i < 32; i++) {
        if (n & (1u << (31 - i))) { // ✅ use 1u
            res |= (1u << i);
        }
    }
    return res;
}
```

**Why `1u`?**
- `1` is signed int → `1 << 31` is UB
- `1u` is unsigned → `1u << 31` is safe and defined

---

### 2.2 Bitwise Addition Example
```cpp
int getSum(int a, int b) {
    unsigned int ua = a, ub = b;
    while (ub != 0) {
        unsigned int carry = (ua & ub) << 1; // ✅ safe
        ua = ua ^ ub;
        ub = carry;
    }
    return (int)ua;
}
```

**Why convert to unsigned?**
- `(a & b) << 1` can overflow sign bit → UB for signed int
- For unsigned, overflow = wrap-around (safe)

---

## 3. Quick Reference Table

| Operation                           | Signed Behavior        | Unsigned Behavior      |
|------------------------------------|------------------------|-------------------------|
| `<<` shift into sign bit           | **UB**                | **Defined** (wrap mod) |
| `>>` on negative                   | Impl-defined (arith.) | Logical shift (0-fill) |
| Overflow on addition/subtraction   | **UB**                | Wrap-around mod 2^n    |
| Bitwise AND, OR, XOR               | Defined               | Defined                |

---

## 4. Safe Coding Principles
- **Rule 1**: Use `unsigned` for bitwise operations, especially shifts
- **Rule 2**: For shift constants, use `1u` or `1UL`, not `1`
- **Rule 3**: Avoid mixing signed/unsigned in comparisons; cast explicitly if needed

---

## 5. Safe Implementation Examples

### Reverse Bits (32-bit)
```cpp
#include <cstdint>

uint32_t reverseBits(uint32_t n) {
    uint32_t res = 0;
    for (int i = 0; i < 32; i++) {
        if (n & (1u << (31 - i))) {
            res |= (1u << i);
        }
    }
    return res;
}
```

### Bitwise Sum Without `+`
```cpp
#include <cstdint>

int getSum(int a, int b) {
    unsigned int ua = a, ub = b;
    while (ub != 0) {
        unsigned int carry = (ua & ub) << 1;
        ua ^= ub;
        ub = carry;
    }
    return (int)ua;
}
```

---

## ✅ Key Takeaways
- Signed shift into sign bit → UB
- Always use `unsigned` for shifts & bit-level manipulation
- Wrap-around on unsigned overflow is well-defined
- Add explicit casts to avoid signed/unsigned mix warnings
