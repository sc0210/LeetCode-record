# C++ 物件導向程式設計（OOP）

物件導向包含四個部分：抽象或類別(Abstraction, Class)、繼承(Inheritance)、多型(Polymorphism)、封裝(Encapsulation)

- **類別(Class):** 類別是物件的藍圖或模板，定義了物件的屬性和方法。
- **封裝(Encapsulation):** 將物件的資料和方法捆綁在一起，並對外部隱藏物件的內部細節，只通過公共介面(方法) 訪問。
- **繼承(Inheritance):** 允許一個類別繼承另一個類別的屬性和方法，並可以添加或修改這些屬性和方法。
- **多型(Polymorphism):** 允許不同的物件對相同的訊息做出不同的響應，即相同的函數名可以有不同的實現。

## 1. 類別 (Class)

類別是物件的藍圖，封裝了資料（成員變數）與行為（成員函式）。

```cpp
class Animal {
public:
    void eat() {
        std::cout << "Animal eating\n";
    }
private:
    int age;
};
```

## 2. 繼承 (Inheritance)

子類別繼承自父類別，可重複使用行為並擴充功能。

```cpp
class Dog : public Animal {
public:
    void bark() {
        std::cout << "Woof!\n";
    }
};
```

繼承型態影響基底成員在子類的可見度：

- public：維持原有的 public/protected。
- protected：public 成員變成 protected。
- private：全部變成 private。

## 3. 虛擬函式與多態 (Virtual Functions & Polymorphism)

虛擬函式允許使用基底指標呼叫子類別覆寫的函式（動態綁定）。

### 3-1. 方法

- 父類別中的函式必須是 `virtual`: 才會啟用「動態綁定」機制（polymorphism），否則呼叫會被靜態綁定（compile-time）。
- 子類別中覆寫函式應加上 `override`。 (雖然不是「強制性的語法」，但強烈建議加上 `override`，避免靜態遮蔽錯誤。）

### 3-2. 正確範例：

```cpp
class Animal {
public:
    virtual void speak() {
        std::cout << "Animal sound\n";
    }
};

class Dog : public Animal {
public:
    void speak() override {
        std::cout << "Woof!\n";
    }
};

void makeSpeak(Animal& a) {
    a.speak();
}
```

### 3-3. 錯誤範例（未加入`virtial`）:

因為 `greet()` 不是 `virtual`，會被靜態綁定。多型（Polymorphism）不會發生。

```cpp
class Parent {
public:
    void greet() {  // 沒有 virtual
        std::cout << "Hello from Parent\n";
    }
};

class Child : public Parent {
public:
    void greet() {
        std::cout << "Hello from Child\n";
    }
};

int main() {
    Parent* p1 = new Child();
    p1->greet();  // 呼叫的是 Parent 的 greet，不是 Child 的

    Child* p2 = new Child();
    p2->greet();  // 呼叫的是 Child 的 greet，不是 Parent 的
}

```

## 4. 抽象類別與「純虛擬函式」 (Abstract Class)

### 4-1. 抽象類別無法實例化，只能透過繼承使用。

- 純虛擬函式是一種「只宣告、不實作」的虛擬函式，目的是讓子類必須自己實作這個函式。
- 一個類別只要有「至少一個」純虛擬函式（`virtual func() = 0;`），它就變成抽象類別，不能直接實體化（new 或 建構變數）。

```cpp
class Shape {
public:
    virtual void draw() = 0; // 純虛擬函式
};
```

這個 `= 0` 表示這是一個純虛擬函式（pure virtual function）。

### 4-2. 範例

```cpp
#include <iostream>

class Shape {
public:
    virtual void draw() = 0;  // 純虛擬函式
    virtual ~Shape() = default;  // 虛擬解構子，確保釋放資源
};

class Circle : public Shape {
public:
    void draw() override {
        std::cout << "畫一個圓形\n";
    }
};

class Square : public Shape {
public:
    void draw() override {
        std::cout << "畫一個正方形\n";
    }
};

int main() {
    // Shape s;            // ❌ 錯誤！抽象類別不能被實體化
    Shape* shape = new Circle();  // ✅ 透過指標使用
    shape->draw();  // 輸出：畫一個圓形
    delete shape;
}
```

### 4-3. 為什麼需要抽象類別？

抽象類別常用來設計「介面」（interface）

- 定義一組共同操作方法，但不實作。
- 讓子類來實作細節。
- 增加程式的彈性與擴充性。
- 例如：

    ```cpp
    class ISerializable {
    public:
        virtual void serialize() = 0;
        virtual ~ISerializable() {}
    };
    ```

## 5. 虛擬解構子 (Virtual Destructor)

當用 **基底(base)** 指標刪除 **子類物件(derived)** 時，需使用 **虛擬解構子(Virtual Destructor)** 來正確釋放資源。

## 5-2. 錯誤範例（沒有 `virtual`）:

```cpp
class Base {
public:
    ~Base() { std::cout << "Base destroyed\n"; }
};

class Derived : public Base {
public:
    ~Derived() { std::cout << "Derived destroyed\n"; }
};

int main() {
    Base* obj = new Derived();
    delete obj;  // 只會呼叫 ~Base()
}
```

輸出：

```shell
Base destroyed
```

Derived 的資源不會被釋放，造成 記憶體洩漏（memory leak）或邏輯錯誤。

## 5-3. 正確範例（有 `virtual` 解構子）：

```cpp
class Base {
public:
    virtual ~Base() { std::cout << "Base destroyed\n"; }
};

class Derived : public Base {
public:
    ~Derived() { std::cout << "Derived destroyed\n"; }
};

int main() {
    Base* obj = new Derived();
    delete obj;  // 正確呼叫 Derived 與 Base 的解構子
}
```

輸出：

```shell
Derived destroyed
Base destroyed
```

## 5-4. 小結：

派生類別（Derived）和基底類別（Base）的資源都會被正確釋放。

| 項目       | 普通解構子          | 虛擬解構子 (`virtual ~`) |
| -------- | -------------- | ------------------- |
| 多型刪除子類指標 | ❌ 只呼叫 base 解構子 | ✅ 會依繼承順序呼叫所有解構子     |
| 適合用於     | 沒有繼承或不會透過指標刪除  | 有繼承、多型、抽象介面等場景      |
| 有無效能差異   | 幾乎沒有           | 幾乎沒有                |


## 6. C++ 多型與物件建立方式比較

| 語句                              | 合法性         | 多型性     | 說明                                      |
| ------------------------------- | ----------- | ------- | --------------------------------------- |
| `Base* obj = new Derived();`    | ✅ 合法        | ✅ 有動態派發 | 常見於多型用途，基類指標指向子類物件，並透過 `virtual` 函式實現多型 |
| `Base* obj = new Base();`       | ✅ 或 ❌ 視情況而定 | ❌ 無多型   | 如果 `Base` 是抽象類別則不合法；否則只是單純指標用法          |
| `Derived* obj = new Derived();` | ✅ 合法        | ❌ 無多型   | 一般用法，無法享有多型好處，只能使用 `Derived` 的功能        |

### 6-2. ✅ Base* obj = new Derived(); 多型行為（推薦使用）

```cpp
class Base {
public:
    virtual void say() { std::cout << "Base\n"; }
};

class Derived : public Base {
public:
    void say() override { std::cout << "Derived\n"; }
};

int main() {
    Base* obj = new Derived();
    obj->say();  // 輸出：Derived
    delete obj;
}
```

### 6-3. ⚠️ Base* obj = new Base();（如果 Base 是具象類）

```cpp
class Base {
public:
    void say() { std::cout << "Base\n"; }
};

int main() {
    Base* obj = new Base();  // 合法，但無多型意義
    obj->say();              // 輸出：Base
    delete obj;
}
```

### 6-4. ❌ Base* obj = new Base();（如果 Base 是抽象類別）

```cpp
class Base {
public:
    virtual void say() = 0;  // 純虛擬函式 → 抽象類
};

int main() {
    Base* obj = new Base();  // 編譯錯誤：抽象類別不能被實例化
}
```

### 6-5. ✅ Derived* obj = new Derived();（非多型）

```cpp
class Derived {
public:
    void say() { std::cout << "Derived\n"; }
};

int main() {
    Derived* obj = new Derived();  // 合法，但只能用 Derived 的方法
    obj->say();                    // 輸出：Derived
    delete obj;
}
```

## 7. `final` 用法

### 7-1. `final` 用來禁止類別被繼承

```cpp
class Animal final {
    // ...
};
```

- 表示這個類別不能被繼承。
- 如果有類別嘗試繼承 Animal，會產生編譯錯誤。

```cpp
class Dog : public Animal {};  // 錯誤，Animal 是 final 類別
```

### 7-2. `final` 用來禁止虛擬函式被覆寫

```cpp
class Animal {
public:
    virtual void speak() final {
        std::cout << "Animal speak\n";
    }
};
```

`speak()` 加上 `final` 後，子類別無法覆寫這個函式。

```cpp
class Dog : public Animal {
public:
    void speak() override {  // 編譯錯誤，不能覆寫 final 函式
        std::cout << "Dog speak\n";
    }
};
```

### 7-3. `final` 的範例整合

```cpp
class Base {
public:
    virtual void run() {
        std::cout << "Base run\n";
    }

    virtual void stop() final {
        std::cout << "Base stop\n";
    }
};

class Derived : public Base {
public:
    void run() override {
        std::cout << "Derived run\n";
    }

    // void stop() override {}  // 錯誤，stop() 是 final，不能覆寫
};

// 以下宣告錯誤，因為 MoreDerived 是 final 類別
class MoreDerived final : public Derived {};

// class CannotInherit : public MoreDerived {};  // 錯誤，不能繼承 final 類別
```

### 7-4. 使用建議

通常搭配 `override` 一起用：

```cpp
void func() override final;  // 表示覆寫父類函式，且不能再被覆寫
```

使用 `final` 可以避免意外覆寫，讓程式設計更安全、更清楚。

### 7-5. 小結

| 用途                       | 說明           |
| ------------------------ | ------------ |
| `class X final`          | 禁止此類別被繼承     |
| `virtual void f() final` | 禁止此虛擬函式被子類覆寫 |

## 完整範例程式

```cpp
#include <iostream>
#include <vector>
#include <memory>

class Shape {
public:
    virtual void draw() const = 0; // 純虛擬函式
    virtual ~Shape() {
        std::cout << "Shape destroyed\n";
    }
};

class Circle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing Circle\n";
    }
    ~Circle() {
        std::cout << "Circle destroyed\n";
    }
};

class Rectangle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing Rectangle\n";
    }
    ~Rectangle() {
        std::cout << "Rectangle destroyed\n";
    }
};

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;

    shapes.push_back(std::make_unique<Circle>());
    shapes.push_back(std::make_unique<Rectangle>());

    for (const auto& shape : shapes) {
        shape->draw();  // 多態：會根據實際型態呼叫對應的 draw()
    }

    // 釋放資源時，會依序呼叫各類別的解構子
    return 0;
}
```

## 小結

| 概念                 | 說明                                 |
| ------------------ | ---------------------------------- |
| `class`            | 封裝資料與方法的基本單位                       |
| `inheritance`      | 子類別重用父類別行為，支援層級化設計                 |
| `virtual`          | 支援多態（動態綁定）                         |
| `override`         | 明確表示覆寫父類別的虛擬函式                     |
| `= 0`              | 純虛擬函式，形成抽象類別                       |
| `virtual ~Class()` | 確保刪除物件時呼叫正確解構子，避免資源洩漏              |
| `noexcept`         | 保證函式不會丟例外，提升安全與效能（違反會觸發 terminate） |

