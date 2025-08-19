# C++ Lambda 函數整理筆記

## 1. Lambda 基本語法
[捕獲列表](參數列表) -> 返回型別 { 函數體 };

- **捕獲列表** [ ]：決定 lambda 可以使用外部變數
    
    - `[]` → 不捕獲外部變數
    - `[=]` → 值捕獲 (copy)
    - `[&]` → 引用捕獲
    - `[x, &y]` → x 值捕獲, y 引用捕獲

- **參數列表** ( )：函數參數，類似普通函數
- **返回型別** -> type：可省略，編譯器自動推導
- **函數體** { }：lambda 實作內容

## 2. Lambda 在 sort 中的範例

```cpp
#include <vector>
#include <algorithm>
#include <iostream>

int main() {
    std::vector<int> v = {5, 2, 8, 1};

    // 升序排序 (自動推導返回型別)
    std::sort(v.begin(), v.end(), [](int a,int b){ return a < b; });

    // 降序排序
    std::sort(v.begin(), v.end(), [](int a,int b){ return a > b; });

    for(auto x:v) std::cout << x << " "; // 8 5 2 1
}
```

## 3. Lambda 捕獲外部變數範例

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int factor = 10;
    vector<int> v = {1,2,3,4};

    // 對元素乘以 factor 後排序
    sort(v.begin(), v.end(), [factor](int a,int b){ return a*factor < b*factor; });

    for(auto x:v) cout << x << " "; // 1 2 3 4
}
```

## 4. Lambda 作為自訂比較器使用

priority_queue 範例

```cpp
#include <queue>
#include <vector>
#include <iostream>
using namespace std;

int main() {
    vector<int> nums = {10, 5, 20};

    auto cmp = [](int a,int b){ return a>b; }; // 最小堆
    priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);

    for(int n:nums) pq.push(n);

    while(!pq.empty()){
        cout << pq.top() << " "; // 5 10 20
        pq.pop();
    }
}
```

> `decltype(cmp)` → 用 lambda 的型別作為比較器模板參數

## 5. Lambda 作為 map / set 自訂排序

```cpp
#include <set>
#include <iostream>
using namespace std;

int main() {
    auto cmp = [](int a,int b){ return a>b; }; // 降序
    set<int, decltype(cmp)> s(cmp);

    s.insert(10);
    s.insert(5);
    s.insert(20);

    for(int x:s) cout << x << " "; // 20 10 5
}
```

## 6. 小結

- Lambda 可以作為 **短小函數**、**inline 比較器**

- 常用在 STL：
    - `sort(v.begin(), v.end(), lambda)`
    - `priority_queue<T, Container, lambda>`
    - `set<T, lambda> / map<Key, Value, lambda>`

- 捕獲列表 [ ] 控制外部變數可見性
- `decltype(lambda)` 可以用來給 STL 容器指定比較器型別