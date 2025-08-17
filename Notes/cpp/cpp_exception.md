# C++例外處理

## 1. 基本語法

```cpp
try {
    // 嘗試執行可能會發生錯誤的程式碼
    if (some_error_condition) {
        throw std::runtime_error("發生錯誤！");
    }
} catch (const std::exception& e) {
    // 處理例外
    std::cout << "捕捉到例外：" << e.what() << std::endl;
}
```

- `throw`：丟出例外物件。
- `try`：包住可能會丟例外的程式碼。
- `catch`：捕捉特定類型的例外。

## 2. 常見的標準例外型別

### 2-1. C++ STL 提供了一些常用的例外類別（都繼承自`std::exception`）：

```cpp
#include <stdexcept> // 包含以下例外類型

throw std::logic_error("邏輯錯誤");
throw std::invalid_argument("無效參數");
throw std::out_of_range("超出範圍");
throw std::runtime_error("執行階段錯誤");
```

### 2-2. 多個catch區塊

- 多個 `catch` 可以針對不同錯誤做不同處理。
- 捕捉順序很重要：越具體的錯誤要放前面。

    ```cpp
    try {
        // ...
    } catch (const std::out_of_range& e) {
        std::cerr << "範圍錯誤: " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "其他錯誤: " << e.what() << "\n";
    }
    ```

### 2-3. 捕捉所有例外

- 這會捕捉任何未列出的例外（不推薦頻繁使用，除非真的不清楚例外來源）。

    ```cpp
    try {
        // ...
    } catch (...) {
        std::cerr << "捕捉到未知例外\n";
    }
    ```

## 3.自訂例外類別

```cpp
class MyException : public std::exception {
public:
    const char* what() const noexcept override {
        return "自訂例外";
    }
};

throw MyException();
```

## 4. `noexcept` — 表示函式不會丟例外

```cpp
void func() noexcept {
    // 不會丟出例外
}
```

- `noexcept` 表示函式保證不會丟出例外。
- 若真的丟出例外，會呼叫 `std::terminate()` 直接結束程式。

### 4-1. 條件式 `noexcept`

可以根據條件判斷函式是否為 `noexcept`：

```cpp
template<typename T>
void foo(T&& t) noexcept(noexcept(t.doSomething())) {
    t.doSomething();
}
```

### 4-2. 為什麼要用 noexcept？

- 性能優化：像是標準容器在決定是否使用 move constructor 時，會看是否是 noexcept，提升效率。
- 更安全：避免不該丟例外的函式在執行時拋出例外，導致不易預期的錯誤。
- 明確介面契約：讓呼叫者知道該函式是否會丟例外。

### 4-3. 搭配例外處理與 noexcept

```cpp
#include <iostream>
#include <stdexcept>

void mightThrow(bool flag) {
    if (flag) throw std::runtime_error("發生錯誤");
}

void safeFunc() noexcept {
    std::cout << "這個函式不會丟例外\n";
}

int main() {
    try {
        mightThrow(true);
    } catch (const std::exception& e) {
        std::cout << "捕捉到例外：" << e.what() << "\n";
    }

    safeFunc(); // 保證不會丟例外
}
```

## 5. 使用例外的建議

| 做法 👍                       | 不建議 👎                      |
| --------------------------- | --------------------------- |
| 用在初始化失敗、資源錯誤等無法避免的情況        | 當作邏輯分支替代品                   |
| 捕捉特定型別（不要用 `catch(...)` 遮蔽錯誤） | 在效能敏感區頻繁使用                  |
| 在庫設計中提供清楚例外訊息               | 在 `destructors` 丟出例外（會導致程式終止） |

## 6. 小技巧：RAII 和例外安全

例外發生時會展開堆疊（stack unwinding），這會呼叫 所有在過程中已建構的物件的 destructor。這就是為什麼 C++ 非常推崇 RAII (Resource Acquisition Is Initialization)。

```cpp
class File {
public:
    File(const std::string& name) {
        f = fopen(name.c_str(), "r");
        if (!f) throw std::runtime_error("開檔失敗");
    }
    ~File() {
        if (f) fclose(f);
    }
private:
    FILE* f;
};
```
