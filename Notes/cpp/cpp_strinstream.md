# `stringstream` 格式化進階技巧

## 1. 進位制轉換

```cpp
#include <sstream>
#include <iomanip>
#include <iostream>

int main() {
    int x = 255;

    std::stringstream ss1;
    ss1 << std::dec << x; // 十進位
    std::cout << ss1.str() << "\n"; // "255"

    std::stringstream ss2;
    ss2 << std::hex << x; // 十六進位 (小寫)
    std::cout << ss2.str() << "\n"; // "ff"

    std::stringstream ss3;
    ss3 << std::hex << std::uppercase << x; // 十六進位 (大寫)
    std::cout << ss3.str() << "\n"; // "FF"

    std::stringstream ss4;
    ss4 << std::oct << x; // 八進位
    std::cout << ss4.str() << "\n"; // "377"
}
```

## 2. 指定寬度 (`setw`)

```cpp
#include <sstream>
#include <iomanip>
#include <iostream>

int main() {
    int x = 42;
    std::stringstream ss;

    ss << std::setw(5) << x; 
    std::cout << ss.str() << "\n"; // "   42" (預設右對齊，補空白)
}
```

## 3. 補零 (`setfill`)

```cpp
#include <sstream>
#include <iomanip>
#include <iostream>

int main() {
    int x = 42;
    std::stringstream ss;

    ss << std::setw(5) << std::setfill('0') << x;
    std::cout << ss.str() << "\n"; // "00042"
}
```

## 4. 左對齊 / 右對齊 (`left`, `right`)

```cpp
#include <sstream>
#include <iomanip>
#include <iostream>

int main() {
    int x = 42;

    std::stringstream ss1;
    ss1 << std::setw(5) << std::left << x;
    std::cout << ss1.str() << "\n"; // "42   "

    std::stringstream ss2;
    ss2 << std::setw(5) << std::right << x;
    std::cout << ss2.str() << "\n"; // "   42"
}
```

## 5. 整合範例

```cpp
#include <sstream>
#include <iomanip>
#include <iostream>

int main() {
    int x = 255;
    std::stringstream ss;

    ss << "十進位: " << std::dec << x << "\n"
       << "十六進位(小寫): " << std::hex << x << "\n"
       << "十六進位(大寫): " << std::hex << std::uppercase << x << "\n"
       << "八進位: " << std::oct << x << "\n"
       << "補零(寬度8): " << std::setw(8) << std::setfill('0') << std::dec << x << "\n";

    std::cout << ss.str();
}
```

```shell
輸出：

十進位: 255
十六進位(小寫): ff
十六進位(大寫): FF
八進位: 377
補零(寬度8): 00000255
```

## 📌 總結

- 進位制 → `std::dec`, `std::hex`, `std::oct (+ std::uppercase)`
- 寬度 → `std::setw(N)`
- 補字元 → `std::setfill('0')`
- 對齊方式 → `std::left`, `std::right`
