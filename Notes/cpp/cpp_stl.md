# C++ STL 常用容器操作筆記

以下為各個常用 STL 容器的操作整理，包括插入、查詢、刪除、遍歷等：

---

## 1. `vector<T>`

* 新增元素：`v.push_back(val);`
* 插入元素：`v.insert(pos, val);`
* 移除最後：`v.pop_back();`
* 隨機訪問：`v[i]`, `v.at(i)`
* 刪除元素：`v.erase(pos);`
* 清空：`v.clear();`
* 大小：`v.size()`, `v.empty()`

## 2. `map<Key, Value>`

* 插入元素：`m[key] = val;`, `m.insert({key, val});`
* 查找元素：`m.find(key);`
* 移除元素：`m.erase(key);`
* 是否存在：`m.count(key)`
* 清空：`m.clear();`

## 3. `unordered_map<Key, Value>`

* 插入元素：`um[key] = val;`, `um.insert({key, val});`
* 查找元素：`um.find(key);`
* 移除元素：`um.erase(key);`
* 是否存在：`um.count(key)`
* 清空：`um.clear();`

## 4. `set<T>`

* 插入元素：`s.insert(val);`
* 移除元素：`s.erase(val);`
* 查找元素：`s.find(val);`
* 是否存在：`s.count(val)`
* 清空：`s.clear();`

## 5. `unordered_set<T>`

* 插入元素：`us.insert(val);`
* 移除元素：`us.erase(val);`
* 查找元素：`us.find(val);`
* 是否存在：`us.count(val)`
* 清空：`us.clear();`

## 6. `priority_queue<T>`

* 加入元素：`pq.push(val);`
* 取出最大：`pq.top();`
* 移除最大：`pq.pop();`
* 判斷是否為空：`pq.empty();`
* 大小：`pq.size();`

## 7. `list<T>`

* 加入到前：`lst.push_front(val);`
* 加入到後：`lst.push_back(val);`
* 移除前：`lst.pop_front();`
* 移除後：`lst.pop_back();`
* 插入元素：`lst.insert(it, val);`
* 刪除元素：`lst.erase(it);`
* 反轉：`lst.reverse();`
* 排序：`lst.sort();`

## 8. `stack<T>`

* 推入元素：`st.push(val);`
* 取出頂部：`st.top();`
* 移除頂部：`st.pop();`
* 判斷是否為空：`st.empty();`
* 大小：`st.size();`

--- 

# STL Containers Detailed Notes

## Common STL Containers Overview

| Container        | Ordered | Unique Elements | Search Time        | Insertion/Deletion        | Notes                                |
| ---------------- | ------- | --------------- | ------------------ | ------------------------- | ------------------------------------ |
| `vector`         | Yes     | No              | O(1) random access | O(n) middle insert/delete | Dynamic array                        |
| `map`            | Yes     | Yes (by key)    | O(log n)           | O(log n)                  | Red-black tree                       |
| `unordered_map`  | No      | Yes (by key)    | O(1) average       | O(1) average              | Hash table                           |
| `set`            | Yes     | Yes             | O(log n)           | O(log n)                  | Red-black tree, key = value          |
| `unordered_set`  | No      | Yes             | O(1) average       | O(1) average              | Hash table                           |
| `priority_queue` | No      | N/A             | Top = O(1)         | Push/Pop = O(log n)       | Max-heap by default                  |
| `list`           | Yes     | No              | O(n) search        | O(1) insert/delete        | Doubly linked list, no random access |

---

## `vector`

* Dynamic array (contiguous memory)
* Fast random access: O(1)
* Slow insert/delete at middle/front: O(n)

### Common Operations:

```cpp
std::vector<int> v;
v.push_back(10);
v.insert(v.begin() + 1, 20);
v.erase(v.begin() + 2);
```

---

## `map`

* Ordered key-value pairs
* Backed by balanced binary search tree (Red-Black Tree)
* Keys are **unique and sorted**

### Common Operations:

```cpp
std::map<string, int> m;
m["apple"] = 3;
m.insert({"banana", 5});
m.erase("apple");
```

---

## `unordered_map`

* Hash table-based key-value pairs
* Keys are unique, **no guaranteed order**
* Faster than `map` in average case

### Common Operations:

```cpp
std::unordered_map<string, int> umap;
umap["x"] = 1;
umap.insert({"y", 2});
umap.erase("x");
```

---

## `set`

* Stores **unique sorted elements**
* Backed by red-black tree

### Common Operations:

```cpp
std::set<int> s;
s.insert(5);
s.insert(3);
s.erase(5);
```

---

## `unordered_set`

* Stores **unique** elements, order not preserved
* Faster than `set` on average due to hashing

### Common Operations:

```cpp
std::unordered_set<int> uset;
uset.insert(100);
uset.erase(100);
if (uset.count(100)) { ... }
```

---

## `priority_queue`

* Max-heap by default (top() is largest)

### Common Operations:

```cpp
std::priority_queue<int> pq;
pq.push(10);
pq.push(5);
pq.pop();
int top = pq.top();
```

* For min-heap:

```cpp
std::priority_queue<int, vector<int>, greater<int>> minHeap;
```

---

## `list` (Doubly Linked List)

* Part of STL `std::list`
* Supports fast insertion/deletion at **any** position: O(1)
* No random access (unlike `vector`)

### Common Operations:

```cpp
#include <list>
std::list<int> myList = {1, 2, 3};

myList.push_back(4);     // [1, 2, 3, 4]
myList.push_front(0);    // [0, 1, 2, 3, 4]

auto it = myList.begin();
std::advance(it, 2);     // Move iterator to 3rd element
myList.insert(it, 99);   // [0, 1, 99, 2, 3, 4]

myList.remove(2);        // Remove all elements == 2
```