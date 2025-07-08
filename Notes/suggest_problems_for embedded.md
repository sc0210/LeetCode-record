
# 🔧 適合嵌入式/韌體求職者的 LeetCode 刷題清單

## 🧠 1. Bit Manipulation（訓練 register、flag 操作思維）

| 題號  | 題名                           | 備註                         |
| --- | ---------------------------- | -------------------------- |
| 191 | Number of 1 Bits             | Hamming Weight，常見硬體計數應用    |
| 136 | Single Number                | XOR 基本性質                   |
| 201 | Bitwise AND of Numbers Range | 位元共通前綴                     |
| 338 | Counting Bits                | DP + 位元操作                  |
| 371 | Sum of Two Integers          | 用位元運算模擬加法器                 |
| 231 | Power of Two                 | `(n & (n - 1)) == 0` 是常見技巧 |
| 260 | Single Number III            | 進階 XOR 拆分技巧                |

---

## 🧵 2. Pointers / Linked List / Memory Safety

| 題號  | 題名                               | 備註                    |
| --- | -------------------------------- | --------------------- |
| 206 | Reverse Linked List              | 必備，考指標交換邏輯            |
| 21  | Merge Two Sorted Lists           | Dummy pointer、遞迴版本也可練 |
| 19  | Remove Nth Node From End of List | double pointer 設計     |
| 160 | Intersection of Two Linked Lists | 比較 pointer 位址         |
| 2   | Add Two Numbers                  | 記憶體配置與 carry 管理       |
| 234 | Palindrome Linked List           | 快慢指標 + reverse 技巧     |

---

## 🧱 3. Array & Memory Access Simulation

| 題號  | 題名                                  | 備註                          |
| --- | ----------------------------------- | --------------------------- |
| 283 | Move Zeroes                         | In-place 模擬                 |
| 26  | Remove Duplicates from Sorted Array | memory overwrite 實務技巧       |
| 167 | Two Sum II - Input Array Is Sorted  | 雙指標應用                       |
| 75  | Sort Colors                         | Dutch National Flag，嵌入式經典題型 |
| 11  | Container With Most Water           | Two pointer 經典題型            |

---

## ⏱️ 4. Queue / Stack / State Machines

| 題號  | 題名                 | 備註                     |
| --- | ------------------ | ---------------------- |
| 20  | Valid Parentheses  | Stack + FSM 思維         |
| 739 | Daily Temperatures | 單調堆疊（模擬感測器資料）          |
| 394 | Decode String      | 字串堆疊模擬狀態轉換             |
| 155 | Min Stack          | Stack 擴充，邏輯清楚          |
| 146 | LRU Cache          | 系統常用資料結構，練習 list + map |

---

## ⏳ 5. Others（常見 C/C++ 陷阱類）

| 題號  | 題名                               | 備註                  |
| --- | -------------------------------- | ------------------- |
| 128 | Longest Consecutive Sequence     | `unordered_set` 的使用 |
| 150 | Evaluate Reverse Polish Notation | stack 模擬記憶體運算       |
| 268 | Missing Number                   | 整數溢位 / XOR / 高效技巧   |
| 88  | Merge Sorted Array               | C++ STL `sort` 也可練  |

---

如需加入難易度、題目連結、或進一步延伸主題（如位元加速技巧、cache 模擬），可再補充我會協助更新。
