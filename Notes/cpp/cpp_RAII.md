# C++ RAII 筆記：Resource Acquisition Is Initialization

## 1. 什麼是 RAII？

RAII（Resource Acquisition Is Initialization）是一種 C++ 程式設計中**自動資源管理**的設計模式。

> **資源的獲取與釋放，應綁定在物件的生命週期中。**

- 建構子：取得資源（記憶體、檔案、鎖…）
- 解構子：釋放資源（自動清理，避免資源洩漏）

---

## 2. RAII 的目標

| 目標 | 說明 |
|------|------|
| 🧹 自動清理 | 離開 scope 就自動釋放資源（ex: `delete`, `close`, `unlock`） |
| 🛡️ Exception-safe | 即使拋出例外也能安全釋放 |
| 🧠 語意清晰 | 明確表達資源擁有者與使用範圍 |

---

## 3. 適用資源類型

| 資源類型 | 範例 |
|----------|------|
| 記憶體 | `new/delete`、`malloc/free` |
| 檔案 | `open/close`, `std::ifstream`, `ofstream` |
| 鎖 | `mutex`, `std::lock_guard`, `std::unique_lock` |
| 其他 | socket、資料庫連線、thread、GPU buffer 等 |

---

## 範例 1：RAII 管理鎖 (`std::lock_guard`)

```cpp
std::mutex mtx;

void critical_section() {
    std::lock_guard<std::mutex> lock(mtx); // 進入後自動 lock
    // critical section
} // 離開 scope 時自動 unlock
```

## 範例 2：RAII 管理檔案 (std::ifstream)

```cpp
#include <fstream>
#include <string>

void read_file() {
    std::ifstream fin("data.txt"); // 自動開檔
    std::string line;
    while (std::getline(fin, line)) {
        // 處理每行
    } // 離開 scope 自動 close
}
```

## 範例 3：RAII 管理記憶體 (std::unique_ptr)

```cpp
#include <memory>

void use_resource() {
    std::unique_ptr<int> ptr(new int(42)); // 自動取得資源
    // 使用 ptr
} // 離開 scope 自動 delete
```

## 為甚麼要用RAII?

| 問題                   | RAII 的解法                |
| --------------------   | ----------------------- |
| 忘記釋放資源                 | 用解構子自動清理               |
| 多處 return 時漏掉 delete    | 離開 scope 一率釋放           |
| try/catch 內部錯誤沒清乾淨    | 解構子會在 exception 發生時依然執行 |
| 多執行緒同步失敗（忘記 unlock） | 用 `lock_guard` 自動釋放鎖    |

## RAII經典應用工具?

| 工具                                    | 說明                        |
| ------------------------------------- | ------------------------- |
| `std::lock_guard`                     | 自動上/解鎖                    |
| `std::unique_ptr` / `std::shared_ptr` | 自動釋放記憶體                   |
| `std::ifstream` / `std::ofstream`     | 自動開/關檔                    |
| `std::thread`                         | 自動 join / detach（C++11 起） |

## 總結：RAII 是 C++ 的核心管理模式

> **RAII 是一種哲學：「用物件管理資源，讓資源的生命週期自動跟著物件走。」**

- 不需手動釋放
- 不怕記憶體洩漏
- 不怕多重 return 漏掉資源清理
- 適用於 exception 安全的現代 C++ 程式風格
