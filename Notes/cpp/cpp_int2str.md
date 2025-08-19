# C++ 整數 → 字串的方法整理

## 1. std::to_string (C++11+)

```cpp
#include <string>
#include <iostream>

int main() {
    int x = -123;
    std::string s = std::to_string(x); // "-123"
    std::cout << s << "\n";
}
```

### 特點：

- ✅ 最簡單、直覺
- ✅ 支援 `int`, `long`, `long long`, `float`,`double` 等
- ❌ 格式不可控 (例如小數點位數、進位制)

## 2. stringstream
```cpp
#include <sstream>
#include <string>
#include <iostream>

int main() {
    int x = 255;
    std::stringstream ss;
    ss << x;
    std::string s = ss.str(); // "255"
    std::cout << s << "\n";
}
```

### 特點：

- ✅ 可控制格式 (進位制、寬度、補零…)
- ❌ 效能比 `to_string` 慢

## 3. std::format (C++20)
```cpp
#include <format>
#include <iostream>
#include <string>

int main() {
    int x = 42;
    std::string s = std::format("數字是: {}", x); // "數字是: 42"
    std::cout << s << "\n";
}
```

### 特點：

- ✅ 最彈性 (格式化能力類似 Python `f-string`)
- ✅ 可直接排版 (寬度、進位制、浮點數精度…)
- ❌ 需要 **C++20**

## 4. sprintf / snprintf (C 標準)
```cpp
#include <cstdio>
#include <iostream>

int main() {
    int x = 12345;
    char buf[32];
    sprintf(buf, "%d", x); // "12345"
    std::cout << buf << "\n";
}
```

### 特點：

- ✅ 傳統 `C` 方法，速度快
- ✅ 格式化功能完整 (%d, %x, %f 等)
- ❌ 不安全 (`sprintf` 可能 overflow)，建議用 `snprintf`
- ❌ 比 `to_string` 繁瑣

## 5. std::ostringstream + manipulators (更靈活格式控制)

```cpp
#include <sstream>
#include <iomanip>
#include <iostream>

int main() {
    int x = 255;
    std::ostringstream oss;
    oss << std::hex << std::uppercase << x; // 轉成 16 進位大寫
    std::string s = oss.str(); // "FF"
    std::cout << s << "\n";
}
```

## 📊 方法比較表

| 方法                    | C++ 版本 | 格式控制 | 效能 | 特點        |
| --------------------- | ------ | ---- | -- | --------- |
| `std::to_string`      | C++11+ | ❌ 無  | 快  | 最簡單直覺     |
| `stringstream`        | C++98+ | ✅ 強大 | 慢  | 彈性大       |
| `std::format`         | C++20+ | ✅ 最強 | 中  | Python 風格 |
| `sprintf/snprintf`    | C/C++  | ✅ 強大 | 快  | C 風格，注意安全 |
| `ostringstream+manip` | C++98+ | ✅ 強大 | 中  | 可輸出進位制等   |

## ✅ 建議選擇

- 一般用途 → `std::to_string()` (簡單好用)
- 需要格式控制 (寬度、進位制、小數位數) → `std::format` (**C++20**)，舊版用 `stringstream`
- 效能優先 / 舊 C 程式碼 → `snprintf`