# 📘 typedef 使用筆記

`typedef` 可以為既有型別創建新的別名，有助於程式可讀性，特別是在複雜資料型別（如函式指標、陣列、結構體）時。

---

## 📌 基本語法

```c
typedef 現有型別 新名稱;
```

例如：

```c
typedef unsigned int uint;
```

---

## 🔍 常見 typedef 範例與解釋

| 原始型別寫法 | typedef 寫法 | 說明 |
|--------------|---------------|------|
| `int` | `typedef int myint;` | `myint` 等同於 `int` |
| `int *` | `typedef int* intptr;` | `intptr` 是 `int` 的指標 |
| `int arr[10]` | `typedef int array10[10];` | `array10` 是一個含 10 個整數的陣列 |
| `int (*fp)(void)` | `typedef int (*funcptr)(void);` | `funcptr` 是一個回傳 int 的函式指標 |
| `void (*)(int)` | `typedef void (*handler)(int);` | `handler` 是一個參數為 int 的 void 函式指標 |

---

## ⚠️ 常見陷阱

### 1. 指標型別定義容易誤會

```c
typedef char* PCHAR;
PCHAR a, b;  // ⚠️ 只有 a 是指標，b 是 char 變數
```

🔑 建議：使用 `typedef` 定義指標時，一次只定義一個變數。

---

### 2. 陣列與指向陣列指標的差異

```c
typedef int arr5[5];     // arr5 是一個陣列
typedef int (*parr5)[5]; // parr5 是指向陣列的指標
```

---

### 3. 函式指標的 typedef 寫法

```c
typedef void (*SignalHandler)(int);
SignalHandler handler;
```

經典範例（難讀）：

```c
void (*signal(int, void (*)(int)))(int);
```

意思是：
- `signal` 是一個函式
- 參數是 `int` 和 `void (*)(int)`
- 回傳值是 `void (*)(int)`

✅ 建議：用 typedef 將函式指標分離命名可提高可讀性。

---

## 🧠 typedef 閱讀技巧：從內往外讀！

複雜型別的閱讀方式建議從變數名稱開始，**由內往外剝解**。

例如：

```c
typedef int (*PFUNC)(double);
```

- `PFUNC` 是一個指向「參數為 double、回傳 int 的函式」的指標。

---

## 🧰 工具推薦

- [📎 cdecl.org](https://cdecl.org) 線上轉換器：
  > 英文輸入：`declare signal as function (int, pointer to function (int) returning void) returning pointer to function (int) returning void`
  >
  > 自動轉成 C code：

```c
void (*signal(int, void (*)(int)))(int);
```

---

## ✅ 建議

- 使用清楚、有語意的 `typedef` 名稱
- 不要過度濫用指標別名（容易誤解）
- 對於函式指標，一定使用 `typedef` 命名簡化
- 碰到複雜語法 → 拆成 typedef + 使用者語意

---
