# C++ Pointer

## 1. Raw Pointer (`T*`)

* 特性：手動記憶體管理
* 操作：`new` 動態宣告記憶體、`delete`清除記憶體。
* 範例

    ```cpp
    #include <iostream>
    using namespace std;

    int main() {
        int* p = new int(5);      // 配置動態記憶體
        cout << *p << "\n";  // 輸出值：5
        delete p;                 // 釋放記憶體
        p = nullptr;              // 避免懸空指標
    }
    ```

---

## 2. 三大智慧指標（smart pointer）

| 智慧指標類型               | 所在標頭       | 說明                                    |
| -------------------- | ---------- | ------------------------------------- |
| `std::unique_ptr<T>` | `<memory>` | **獨占式擁有權**，不可複製，只能移動                  |
| `std::shared_ptr<T>` | `<memory>` | **共享式擁有權**，用引用計數管理生命週期                |
| `std::weak_ptr<T>`   | `<memory>` | **非擁有式弱引用**，配合 `shared_ptr` 使用，避免循環引用 |

### 智慧指標的特色

* 自動釋放資源（Destructor 自動呼叫 delete）
* 不需手動 delete
* 搭配 STL 容器使用安全又方便
* 搭配 std::make_unique() / std::make_shared() 建立實例更安全高效

## 2-1. `std::unique_ptr<T>`

* 特性：獨占擁有權、自動釋放
* 操作：`make_unique`來宣告 **unique_ptr**、`move`移動指標（無法複製）
* 範例：

    ```cpp
    #include <iostream>
    #include <memory>
    using namespace std;

    int main() {
        unique_ptr<int> up = make_unique<int>(42);
        cout << *up << "\n";      // 輸出：42

        // 轉移所有權(move)，並無複製操作
        unique_ptr<int> up2 = move(up);
        if (!up) cout << "up is null\n";
    }
    ```

---

## 2-2. `std::shared_ptr<T>`

* 特性：多方共享、引用計數、小心循環引用
* 操作：`make_shared`來宣告 **shared_ptr**、
* 範例：

    ```cpp
    #include <iostream>
    #include <memory>
    using namespace std;

    int main() {
        shared_ptr<int> sp1 = make_shared<int>(100);
        shared_ptr<int> sp2 = sp1;  // 共用資源

        cout << *sp1 << ", count: " << sp1.use_count() << "\n";  // count: 2
        sp2.reset();  // sp2 不再持有
        cout << "count after reset: " << sp1.use_count() << "\n";  // count: 1
    }
    ```

---

## 2-3. `std::weak_ptr<T>`

* 特性：非擁有性引用、不增加計數，解決 shared_ptr 循環引用問題
* 範例

    ```cpp
    #include <iostream>
    #include <memory>
    using namespace std;

    int main() {
        shared_ptr<int> sp = make_shared<int>(200);
        weak_ptr<int> wp = sp;  // 弱引用

        if (auto locked = wp.lock()) {
            cout << *locked << "\n";  // 輸出 200
        } else {
            cout << "Pointer expired\n";
        }

        sp.reset();  // 釋放 shared_ptr

        if (wp.lock()) {
            cout << "Still valid\n";
        } else {
            cout << "Now expired\n";  // 指標已失效
        }
    }
    ```

---

## 指標類型比較表

| 類型           | 所有權     | 自動釋放 | 引用計數 | 可複製    | 適用情境               |
|----------------|------------|-----------|-----------|-----------|------------------------|
| `T*`           | ❌          | ❌        | ❌         | ✅        | C-style、嵌入式        |
| `unique_ptr`   | ✅ 獨佔    | ✅        | ❌         | ❌（移動）| 單一擁有者、容器內管理 |
| `shared_ptr`   | ✅ 共用    | ✅        | ✅         | ✅        | 資源共享、複雜結構     |
| `weak_ptr`     | ❌          | ✅        | ❌         | ✅        | 避免 shared_ptr 循環引用 |

---

## 使用技巧

- ✅ 優先使用 `make_unique`, `make_shared`
- ✅ 用 `auto` 推導型別簡潔安全
- ❌ 避免裸指標處理所有權資源
- ✅ 容器中使用 `unique_ptr` 管理動態物件
- ✅ 多人共用資源使用 `shared_ptr`
- ✅ 使用 `weak_ptr` 斷開循環依賴

---

## 📘 延伸資源

- [CppReference - unique_ptr](https://en.cppreference.com/w/cpp/memory/unique_ptr)
- [CppReference - shared_ptr](https://en.cppreference.com/w/cpp/memory/shared_ptr)
- [Herb Sutter: Smart Pointers](https://herbsutter.com/gotw/)