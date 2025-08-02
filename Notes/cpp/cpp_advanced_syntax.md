
# C++ 高階語法與技巧詳解

本筆記彙整 C++ 面試中常見的高階語法與實用技巧，包含 Lambda 表達式、智慧指標、RAII、C++11/14/17 語法特性等。

---

## 🔹 Lambda 表達式與函數指標

### Lambda 表達式語法：
```cpp
[capture](parameters) -> return_type {
    // body
}
```

### 範例：
```cpp
auto add = [](int a, int b) -> int { return a + b; };
std::cout << add(2, 3); // 輸出 5
```

### 捕捉方式：
- `[=]`：以值捕捉外部變數
- `[&]`：以引用捕捉外部變數
- `[x]`：只捕捉 x（以值）

### Lambda 與函數指標：
Lambda 可隱式轉換為函數指標（若不捕捉變數）：
```cpp
void call_func(int (*f)(int)) {
    std::cout << f(5);
}
call_func([](int x) { return x * 2; });
```

---

## 🔹 智慧指標（Smart Pointers）

### unique_ptr
- 擁有唯一物件所有權。
```cpp
std::unique_ptr<int> ptr = std::make_unique<int>(10);
```

### shared_ptr
- 多個 shared_ptr 可共享同一物件所有權。
```cpp
std::shared_ptr<int> ptr1 = std::make_shared<int>(10);
std::shared_ptr<int> ptr2 = ptr1;  // 引用計數增加
```

### weak_ptr
- 解決 shared_ptr 循環引用問題（不增加引用計數）。

---

## 🔹 RAII 與 Scope

### 觀念：
**Resource Acquisition Is Initialization**：
- 使用物件建構與解構來管理資源。
- 常用於檔案、鎖、記憶體等釋放。

### 範例：
```cpp
class FileHandler {
public:
    FileHandler(const std::string& filename) {
        file = fopen(filename.c_str(), "r");
    }
    ~FileHandler() {
        if (file) fclose(file);
    }
private:
    FILE* file;
};
```

---

## 🔹 C++11/14/17 特性

### 1. auto 型別推導
```cpp
auto x = 42;     // int
auto y = 3.14;   // double
```

### 2. range-based for loop
```cpp
std::vector<int> v = {1, 2, 3};
for (auto x : v) std::cout << x;
```

### 3. nullptr 替代 NULL

### 4. move semantics
```cpp
std::string a = "hello";
std::string b = std::move(a); // a 被移動，b 獲得資源
```

### 5. constexpr（編譯期常數）

### 6. structured bindings (C++17)
```cpp
std::tuple<int, std::string> t = {1, "abc"};
auto [id, name] = t;
```

### 7. if constexpr (C++17)
```cpp
template <typename T>
void print_type(T x) {
    if constexpr (std::is_integral<T>::value) {
        std::cout << "int
";
    } else {
        std::cout << "non-int
";
    }
}
```

---

## ✅ 建議練習與複習方向
- 用 Lambda 實作簡易排序與 callback。
- 實作 RAII-style 類別（如鎖、檔案管理）。
- 使用 `shared_ptr` 模擬循環引用並用 `weak_ptr` 解決。
- 撰寫支援 move constructor 的 class。
- 熟悉各版本 C++ 的語法演進。

---
