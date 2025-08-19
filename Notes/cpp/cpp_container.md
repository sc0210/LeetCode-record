# C++ 關聯容器效率比較

## STL: `map` / `set` 操作整理

1. `map<Key, Value>`

- 插入元素

    ```cpp
    mp[key] = value;
    mp.insert({key, value});
    mp.emplace(key, value); (更高效)
    ```

- 查找元素

    ```cpp
    mp.find(key) → 回傳 iterator，若不存在則回傳 mp.end()
    mp.count(key) → 回傳 0 或 1
    ```

- 存取元素

    ```cpp
    mp[key] → 若 key 不存在會建立新元素 (預設值)
    mp.at(key) → 若 key 不存在會拋出例外 (out_of_range)
    ```

- 刪除元素

    ```cpp
    mp.erase(key); → 依 key 刪除
    mp.erase(iterator); → 依 iterator 刪除
    ```

- 其他

    ```cpp
    mp.size() → 元素數量
    mp.empty() → 判斷是否為空
    mp.clear() → 清空
    ```

2. `set<Key>`

- 插入元素

    ```cpp
    st.insert(val);
    st.emplace(val);
    ```

- 查找元素

    ```cpp
    st.find(val) → 回傳 iterator，若不存在則回傳 st.end()
    st.count(val) → 回傳 0 或 1
    ```

- 刪除元素

    ```cpp
    st.erase(val); → 依值刪除
    st.erase(iterator); → 依 iterator 刪除
    ```

- 其他

    ```cpp
    st.size() → 元素數量
    st.empty() → 判斷是否為空
    st.clear() → 清空
    ```

3. `unordered_map<Key, Value>`

- 插入元素

    ```cpp
    ump[key] = value;
    ump.insert({key, value});
    ump.emplace(key, value);
    ```

- 查找元素

    ```cpp
    ump.find(key) → 回傳 iterator，若不存在則回傳 ump.end()
    ump.count(key) → 回傳 0 或 1
    ```

- 存取元素

    ```cpp
    ump[key] → 若 key 不存在會建立新元素 (預設值)
    ump.at(key) → 若 key 不存在會拋出例外 (out_of_range)
    ```

- 刪除元素

    ```cpp
    ump.erase(key); → 依 key 刪除
    ump.erase(iterator); → 依 iterator 刪除
    ```

- 其他

    ```cpp
    ump.size() → 元素數量
    ump.empty() → 判斷是否為空
    ump.clear() → 清空
    ```

4. `unordered_set<Key>`

- 插入元素

    ```cpp
    ust.insert(val);
    ust.emplace(val);
    ```

- 查找元素

    ```cpp
    ust.find(val) → 回傳 iterator，若不存在則回傳 ust.end()
    ust.count(val) → 回傳 0 或 1
    ```

- 刪除元素

    ```cpp
    ust.erase(val); → 依值刪除
    ust.erase(iterator); → 依 iterator 刪除
    ```

- 其他

    ```cpp
    ust.size() → 元素數量
    ust.empty() → 判斷是否為空
    ust.clear() → 清空
    ```

## 1. `map` vs `unordered_map`

| 特性          | `map`                                               | `unordered_map`       |
| ----------- | --------------------------------------------------- | --------------------- |
| **底層實作**    | 平衡二元搜尋樹 (Red-Black Tree)                            | 雜湊表 (Hash Table)      |
| **元素順序**    | 依照 key **自動排序** (遞增)                                | **無序**                |
| **查找時間複雜度** | O(log n)                                            | 平均 O(1)，最壞 O(n)       |
| **插入時間複雜度** | O(log n)                                            | 平均 O(1)，最壞 O(n)       |
| **刪除時間複雜度** | O(log n)                                            | 平均 O(1)，最壞 O(n)       |
| **記憶體使用**   | 較緊湊                                                 | 較大 (需額外存 hash bucket) |
| **適合情境**    | 需要 **有序 key**、範圍查詢 (如 `lower_bound`, `upper_bound`) | 需要 **快速查找**、順序不重要     |

## 2. `set` vs `unordered_set`

| 特性          | `set`                    | `unordered_set`       |
| ----------- | ------------------------ | --------------------- |
| **底層實作**    | 平衡二元搜尋樹 (Red-Black Tree) | 雜湊表 (Hash Table)      |
| **元素順序**    | 依照元素 **自動排序** (遞增)       | **無序**                |
| **查找時間複雜度** | O(log n)                 | 平均 O(1)，最壞 O(n)       |
| **插入時間複雜度** | O(log n)                 | 平均 O(1)，最壞 O(n)       |
| **刪除時間複雜度** | O(log n)                 | 平均 O(1)，最壞 O(n)       |
| **記憶體使用**   | 較緊湊                      | 較大 (需額外存 hash bucket) |
| **適合情境**    | 需要 **排序集合** 或 **範圍操作**   | 需要 **快速查找**、順序不重要     |

## 3. 簡單程式比較 (插入查找效能)

```cpp
#include <iostream>
#include <map>
#include <unordered_map>
#include <chrono>

int main() {
    const int N = 1000000;

    std::map<int,int> m;
    std::unordered_map<int,int> um;

    // 測試 map
    auto start = std::chrono::high_resolution_clock::now();
    for(int i=0;i<N;i++) m[i] = i;
    for(int i=0;i<N;i++) auto it = m.find(i);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "map: " << std::chrono::duration<double>(end-start).count() << "s\n";

    // 測試 unordered_map
    start = std::chrono::high_resolution_clock::now();
    for(int i=0;i<N;i++) um[i] = i;
    for(int i=0;i<N;i++) auto it = um.find(i);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "unordered_map: " << std::chrono::duration<double>(end-start).count() << "s\n";
}
```

> 👉 通常 `unordered_map` 會比 `map` 快 3~10 倍，但最差情況下可能退化到 O(n)。

## 4. 總結比較

| 容器              | 底層結構       | 是否有序 | 插入/查找/刪除 | 遍歷順序 | 記憶體消耗 | 適用場景         |
| --------------- | ---------- | ---- | -------- | ---- | ----- | ------------ |
| `map`           | 紅黑樹        | ✅ 有序 | O(log n) | 升序排列 | 中     | 需要排序、區間查詢    |
| `set`           | 紅黑樹        | ✅ 有序 | O(log n) | 升序排列 | 中     | 需要唯一且排序的元素集合 |
| `unordered_map` | Hash Table | ❌ 無序 | 平均 O(1)  | 無序   | 高     | 快速查找、不需排序    |
| `unordered_set` | Hash Table | ❌ 無序 | 平均 O(1)  | 無序   | 高     | 快速判斷元素是否存在   |

## 5. 小結

- 需要排序、有序遍歷 ➝ `map` / `set`
- 只需快速查找 ➝ `unordered_map` / `unordered_set`
- 記憶體敏感 ➝ 傾向 `map` / `set`
- 大量查找 ➝ 傾向 `unordered_map` / `unordered_set`
