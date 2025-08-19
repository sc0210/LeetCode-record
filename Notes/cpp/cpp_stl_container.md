# C++ STL 常用容器操作總結

| 容器                         | 插入方法                                        | 刪除方法                             | 查找方法 / 存取方法                                          | 特點 / 備註           |
| -------------------------- | ------------------------------------------- | -------------------------------- | ---------------------------------------------------- | ----------------- |
| `stack<T>`                 | `push(val)`                                 | `pop()`                          | `top()`                                              | LIFO (後進先出)       |
| `queue<T>`                 | `push(val)`                                 | `pop()`                          | `front()`, `back()`                                  | FIFO (先進先出)       |
| `priority_queue<T>`        | `push(val)`                                 | `pop()`                          | `top()`                                              | 最大堆 / 最小堆 (依預設比較) |
| `map<Key, Value>`          | `insert({k,v})`, `emplace(k,v)`, `mp[k]=v`  | `erase(key)` / `erase(iterator)` | `find(key)`, `count(key)`, `mp[key]`, `mp.at(key)`   | 有序 key，紅黑樹        |
| `set<Key>`                 | `insert(val)`, `emplace(val)`               | `erase(val)` / `erase(iterator)` | `find(val)`, `count(val)`                            | 有序元素，唯一           |
| `unordered_map<Key,Value>` | `insert({k,v})`, `emplace(k,v)`, `ump[k]=v` | `erase(key)` / `erase(iterator)` | `find(key)`, `count(key)`, `ump[key]`, `ump.at(key)` | 無序 key，哈希表        |
| `unordered_set<Key>`       | `insert(val)`, `emplace(val)`               | `erase(val)` / `erase(iterator)` | `find(val)`, `count(val)`                            | 無序元素，哈希表，唯一       |

## 📌 補充說明

- `stack` / `queue` / `priority_queue` → 線性容器接口，只能從一端存取（`stack LIFO`，`queue FIFO`，`priority_queue` 最大值或最小值優先）。

- `map` / `set` / `unordered_map` / `unordered_set` → 關聯容器接口，可按 key 查找、插入、刪除。

- `unordered` 系列 → 底層是哈希表，平均 O(1)；`map` / `set` → 紅黑樹，O(log n)。

### 插入元素時：

- `stack` / `queue` / `priority_queue` → push

- `map` / `set` / `unordered_map` / `unordered_set` → insert / emplace / [key]=value