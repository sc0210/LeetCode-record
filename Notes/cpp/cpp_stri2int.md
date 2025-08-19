# C++ 字串/字元轉整數方法整理

> 在處理型別轉換時，常見需求是將 string/char → int，尤其要注意 正負號 (sign) 與 錯誤處理。

## 1. atoi (C 函式)

```cpp
#include <cstdlib>

int val = atoi("123");   // 123
int neg = atoi("-45");   // -45
int bad = atoi("abc");   // 0
```

### 特點：

- ✅ 支援正負號 ("-123" → -123, "+99" → 99)
- ❌ 非數字 → 回傳 0，無法區分錯誤
- ❌ 沒有錯誤檢查

> 屬於 C 標準函式，在 C++ 中不建議主要使用。

## 2. stoi (C++11 之後)

```cpp
#include <string>

int val = std::stoi("123");   // 123
int neg = std::stoi("-45");   // -45
int pos = std::stoi("+88");   // 88
```

### 特點：

- ✅ 支援正負號
- ✅ 遇到錯誤會丟例外：
- `std::invalid_argument` → 字串不是數字
- `std::out_of_range` → 超過 int 範圍
- ✅ 還有 `stol` / `stoll` / `stoul` 等對應版本

- ⚠️ 例外處理需要 `try-catch`

    ```cpp
    try {
        int x = std::stoi("abc"); // throw std::invalid_argument
    } catch (std::invalid_argument& e) {
        std::cerr << "不是合法數字！\n";
    }
    ```

## 3. stringstream
```cpp
#include <sstream>
#include <string>

std::string s = "-123";
int num;
std::stringstream ss(s);
ss >> num;  // num = -123
```

### 特點：

- ✅ 支援正負號
- ✅ 可透過 `ss.fail()` 判斷錯誤
- ❌ 效能比 `stoi` 慢

## 4. from_chars (C++17)

```cpp
#include <charconv>
#include <string>

std::string s = "-456";
int num;
auto [ptr, ec] = std::from_chars(s.data(), s.data() + s.size(), num);

if (ec == std::errc()) {
    // ✅ 轉換成功
} else {
    // ❌ 錯誤處理
}
```

### 特點：

- ✅ 支援正負號
- ✅ 無例外，錯誤透過 ec 判斷
- ✅ 效能最佳 (低階 API)
- ❌ 寫法較複雜

## 5. 單個 char → int

```cpp
char c = '7';
int num = c - '0';  // 7
```

### 特點：

- ✅ 快速、簡單
- ⚠️ 僅適用 '0' ~ '9'
- ❌ 非數字字元 → 結果不正確

---

## 📊 方法比較表

| 方法              | 支援正負號   | 錯誤處理       | 效能 | C++ 版本 |
| --------------- | ------- | ---------- | -- | ------ |
| `atoi`          | ✅       | ❌ 無法檢查     | 中等 | C 標準   |
| `stoi`          | ✅       | ✅ 例外處理     | 中等 | C++11+ |
| `stringstream`  | ✅       | ✅ `fail()` | 慢  | C++98+ |
| `from_chars`    | ✅       | ✅ `errc`   | 最快 | C++17+ |
| `c - '0'` (單字元) | ❌ 需確保範圍 | ❌ 無法檢查     | 最快 | C 標準   |

## ✅ 建議

- 一般情境 → `std::stoi` (安全簡單)
- 高效能需求 → `std::from_chars` (C++17+)
- 單字元轉數字 → `c - '0'`
- 舊 C 程式碼 → `atoi` (建議避免新程式使用)

## 📊 C++ 字串轉整數：數值範圍與建議方法

| 數值範圍     | 建議型別      | 建議轉換方法  | 錯誤處理   |
| ------------------------------------------------------------------------------- | -------------------- | -------------------------------------------------------- | ----------------------------------------------------------------------------------- |
| `[-2,147,483,648 ~ 2,147,483,647]` <br>(`int` 範圍)      | `int`                | `std::stoi` <br> `std::from_chars<int>`                  | `stoi` 會丟 `std::out_of_range` <br> `from_chars` 回傳 `std::errc::result_out_of_range` |
| `[-9,223,372,036,854,775,808 ~ 9,223,372,036,854,775,807]` <br>(`long long` 範圍) | `long long`          | `std::stoll` <br> `std::from_chars<long long>`           | 同上，超出範圍會丟例外或回傳錯誤碼                                                                   |
| `[0 ~ 18,446,744,073,709,551,615]` <br>(`unsigned long long` 範圍)                | `unsigned long long` | `std::stoull` <br> `std::from_chars<unsigned long long>` | 超出範圍 → `out_of_range` 或 `errc::result_out_of_range`                                 |
| 大於 `unsigned long long` (2^64-1)                                                | **大數 (Big Integer)** | `boost::multiprecision::cpp_int` <br> GMP / MPIR         | 可處理任意大小數字                                                                           |

## 📌 使用建議

- 日常情境 (一般整數) → 用 `std::stoi`，簡單、安全。
- 高效能場景 → 用 `std::from_chars` (無例外，速度快)。
- 數字可能超過 int → 先用 `stoll`，再手動檢查是否落在 `int` 範圍。
- 極大數字 (超過 64 位元) → 用 `Boost.Multiprecision::cpp_int` 或 `GMP`。
