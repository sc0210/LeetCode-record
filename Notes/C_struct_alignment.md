# 📘 C/C++ 結構體對齊與 Padding 筆記

## ✅ 結構體對齊的基本原則

1. **每個成員變數的起始位址**，必須是其對齊需求（alignment）的倍數。
2. **成員之間如果不對齊**，編譯器會自動插入 padding（填補空間）來對齊下一個成員。
3. **結構體總大小** 必須是 **最大對齊需求成員的倍數**，可能需要尾部 padding。

---

## 📌 範例：`struct B`

```cpp
struct B {
    char a;   // 1 byte
    int b;    // 4 bytes
    short c;  // 2 bytes
    long d;   // 8 bytes (on 64-bit system)
};
```

---

## 📊 分析表格

| 成員      | 大小 | 對齊需求 | 放置位址範圍 | Padding 原因                       | Padding 大小 |
|-----------|------|-----------|---------------|------------------------------------|--------------|
| `char a`  | 1 B  | 1 B       | 0             | 為了對齊 `int b`（需要 4 bytes）    | 3 B          |
| `int b`   | 4 B  | 4 B       | 4–7           | 已對齊                              | 0 B          |
| `short c` | 2 B  | 2 B       | 8–9           | 為了對齊 `long d`（需要 8 bytes）   | 6 B          |
| `long d`  | 8 B  | 8 B       | 16–23         | 已對齊                              | 0 B          |

✅ **結構體總大小：24 bytes**  
✅ **最大對齊需求：8 bytes (`long`)**

---

## 🧠 為什麼 `short c` 後面會加 6 bytes padding？

因為 `long d` 需要對齊到 8-byte 邊界，`c` 結束後 offset 是 10，**不是 8 的倍數**，所以補上 6 bytes，使 `d` 從 offset 16 開始。

---

## ❗ 常見誤解修正

| 誤解                                                       | 正解                                                               |
|------------------------------------------------------------|--------------------------------------------------------------------|
| 每個成員後的 padding 都補到 4 bytes                         | ❌ 錯，**補多少 padding 是根據下一個成員的對齊需求**                   |
| 結構體總大小是所有成員大小總和                             | ❌ 錯，還要加上**padding** 和 **尾部對齊**                              |
| padding 是為了當前成員的 alignment                          | ❌ 錯，padding 是為了**下一個成員** 的 alignment                        |

---

## 🧪 驗證方式（使用 C++）

```cpp
#include <iostream>
#include <cstddef>

struct B {
    char a;
    int b;
    short c;
    long d;
};

int main() {
    std::cout << "sizeof(B) = " << sizeof(B) << "\n";
    std::cout << "offsetof(a) = " << offsetof(B, a) << "\n";
    std::cout << "offsetof(b) = " << offsetof(B, b) << "\n";
    std::cout << "offsetof(c) = " << offsetof(B, c) << "\n";
    std::cout << "offsetof(d) = " << offsetof(B, d) << "\n";
}
```

---

## 📝 小結

- 🔄 **padding 是為了讓下一個成員對齊，而非自己**
- 📏 結構體的總大小，會向上補到最大對齊需求的倍數
- ⚠ 過度使用 padding 可能浪費空間，可透過 **調整成員順序** 或 `#pragma pack` 優化
