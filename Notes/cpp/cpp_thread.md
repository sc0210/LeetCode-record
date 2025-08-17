# C++ 平行與同步機制學習筆記

## 1. `std::thread` 基本使用

### 說明

- 建立 thread 並執行任務
- 使用 `join()` 等待 thread 結束

### 範例

```cpp
#include <iostream>
#include <thread>

void say_hello(int id) {
    std::cout << "Hello from thread " << id << std::endl;
}

int main() {
    std::thread t1(say_hello, 1);
    std::thread t2(say_hello, 2);

    t1.join();
    t2.join();

    std::cout << "Main thread done." << std::endl;
}
```

---

## 2. `std::mutex` 搭配 `thread`

### 說明

- 多個 thread 同時修改資料時需同步保護
- 使用 `std::mutex` 確保臨界區安全

### 範例

```cpp
#include <iostream>
#include <thread>
#include <mutex>

int counter = 0;
std::mutex mtx;

void increment() {
    for (int i = 0; i < 10000; ++i) {
        std::lock_guard<std::mutex> lock(mtx);
        ++counter;
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);

    t1.join();
    t2.join();

    std::cout << "Final counter: " << counter << std::endl;
}
```

---

## 3. `std::atomic` 原子操作

### 說明

- 避免 mutex，適用於簡單資料類型
- lock-free 操作更有效率

### 範例

```cpp
#include <iostream>
#include <thread>
#include <atomic>

std::atomic<int> counter(0);

void add() {
    for (int i = 0; i < 10000; ++i) {
        ++counter;
    }
}

int main() {
    std::thread t1(add);
    std::thread t2(add);

    t1.join();
    t2.join();

    std::cout << "Final counter: " << counter << std::endl;
}
```

---

## 4. `std::condition_variable` 等待/通知

### 說明

- 適用於 thread 間通訊（如 producer-consumer）

### 範例

```cpp
#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

std::queue<int> q;
std::mutex mtx;
std::condition_variable cv;
bool done = false;

void producer() {
    for (int i = 1; i <= 5; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        q.push(i);
        std::cout << "Produced: " << i << std::endl;
        cv.notify_one();
    }
    {
        std::lock_guard<std::mutex> lock(mtx);
        done = true;
        cv.notify_all();
    }
}

void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return !q.empty() || done; });
        while (!q.empty()) {
            int val = q.front();
            q.pop();
            std::cout << "Consumed: " << val << std::endl;
        }
        if (done) break;
    }
}

int main() {
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();
}
```

---

## 5. 簡易 Thread Pool 實作

### 說明

- 建立固定工作者數量
- 使用 queue 分派任務

### 範例（簡化）

```cpp
#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>

class ThreadPool {
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex mtx;
    std::condition_variable cv;
    std::atomic<bool> stop{false};

public:
    ThreadPool(size_t n) {
        for (size_t i = 0; i < n; ++i) {
            workers.emplace_back([this]() {
                while (true) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(mtx);
                        cv.wait(lock, [this] { return stop || !tasks.empty(); });
                        if (stop && tasks.empty()) return;
                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    task();
                }
            });
        }
    }

    void enqueue(std::function<void()> task) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            tasks.push(task);
        }
        cv.notify_one();
    }

    ~ThreadPool() {
        {
            std::lock_guard<std::mutex> lock(mtx);
            stop = true;
        }
        cv.notify_all();
        for (auto& w : workers) w.join();
    }
};

int main() {
    ThreadPool pool(4);
    for (int i = 0; i < 8; ++i) {
        pool.enqueue([i]() {
            std::cout << "Task " << i << " executed by thread " << std::this_thread::get_id() << std::endl;
        });
    }
}
```

---

## 6. `std::async`, `std::future`

### 說明

- 封裝非同步任務，輕量使用方式

### 範例

```cpp
#include <iostream>
#include <future>

int slow_add(int a, int b) {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return a + b;
}

int main() {
    std::future<int> result = std::async(slow_add, 2, 3);
    std::cout << "Doing other work...\n";
    std::cout << "Result: " << result.get() << std::endl;
}
```

---

## 7. 圖論演算法平行化（範例：並行計算節點度數）

### 說明

- 拆分任務由多執行緒處理，最終彙總

### 範例

```cpp
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

std::mutex mtx;
int global_sum = 0;

void compute_degree(const std::vector<std::vector<int>>& graph, int start, int end) {
    int local_sum = 0;
    for (int i = start; i < end; ++i) {
        local_sum += graph[i].size();
    }
    std::lock_guard<std::mutex> lock(mtx);
    global_sum += local_sum;
}

int main() {
    std::vector<std::vector<int>> graph = {
        {1, 2}, {0, 3}, {0}, {1}
    };
    int thread_count = 2;
    int n = graph.size();
    std::vector<std::thread> threads;

    for (int i = 0; i < thread_count; ++i) {
        int start = i * n / thread_count;
        int end = (i + 1) * n / thread_count;
        threads.emplace_back(compute_degree, std::ref(graph), start, end);
    }

    for (auto& t : threads) t.join();
    std::cout << "Total degree: " << global_sum << std::endl;
}
```
