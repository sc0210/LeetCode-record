# sorting

## 1. Bubble sort

* 概念：當遇到比當前數字小者，交換
* Time complexty: O(N^2)

```cpp
void BubbleSort(vector<int>& arr){
    int N = arr.size();
    for(int i = 0; i < N - 1; i++){
        for(int j = 0; j < N - i - 1; j++){
        if(arr[j] > arr[j + 1]){
            swap(arr[j], arr[j + 1]);
            }
        }
    }
}
```

## 2. Selection sort

* 概念：每一次挑選最小的元素放置在第i的位置
* Time complexty: O(N^2)

```cpp
void SelectionSort(vector<int>& arr){
    int N = arr.size();
    for(int i=0; i<N; i++){
        int Index = i;
        for(int j=i+1; j<N; j++){
            // update the most less value index
            if(arr[j]<arr[Index]) Index = j;
        }
        swap(arr[Index], arr[i]);
    }
}
```

## 3. Insertion sort

* 概念：每一次插入一個直到正確的位置
* Time complexty: O(N^2)

```cpp
void InsertionSort(vector<int>& arr){
    int N = arr.size();
    for(int i = 1; i < N; ++i){
        int key = arr[i];  // target value
        int j = i - 1;

        // shift the value that is larger than ley
        while(j >= 0 && arr[j] > key){
            arr[j + 1] = arr[j];
            j--;
        }
        // insert the value in right position
        arr[j + 1] = key;
    }
}
```

## 4. Merge sort

* 概念：Divide-and-conquer，將原本的陣列看做成多個陣列合併，每一次合併會去排序一次
* Time complexty: O(Nlog(N))

```cpp
// Top-down method (recursive)
void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> temp;
    int i = left, j = mid + 1;

    // 合併兩個已排序區間
    while(i <= mid && j <= right) {
        if(arr[i] <= arr[j]) temp.push_back(arr[i++]);
        else temp.push_back(arr[j++]);
    }

    // 左邊剩餘
    while(i <= mid) temp.push_back(arr[i++]);
    // 右邊剩餘
    while(j <= right) temp.push_back(arr[j++]);

    // 將 temp 的結果複製回原陣列
    for(int k = 0; k < temp.size(); ++k)
        arr[left + k] = temp[k];
}

void mergesort(vector<int>& arr, int left, int right) {
    if(left >= right) return;

    int mid = left + (right - left) / 2;
    mergesort(arr, left, mid);
    mergesort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}
```

```cpp
// Bottom-up method
void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> temp;
    int i = left, j = mid + 1;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j])
            temp.push_back(arr[i++]);
        else
            temp.push_back(arr[j++]);
    }

    while (i <= mid) temp.push_back(arr[i++]);
    while (j <= right) temp.push_back(arr[j++]);

    for (int k = 0; k < temp.size(); ++k)
        arr[left + k] = temp[k];
}

void mergesort_bottomup(vector<int>& arr) {
    int N = arr.size();
    // 每次合併的子陣列大小：1 → 2 → 4 → 8 → ...
    for (int size = 1; size < N; size *= 2) {
        for (int left = 0; left < N - size; left += 2 * size) {
            int mid = left + size - 1;
            int right = min(left + 2 * size - 1, N - 1);
            merge(arr, left, mid, right);
        }
    }
}

```

## 5. Quick sort

```cpp
int partition(vector<int>& arr, int left, int right) {
    int pivot = arr[right];  // 選最後一個作為 pivot
    int i = left - 1;

    for(int j = left; j < right; j++) {
        if(arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[right]);
    return i + 1;  // 回傳 pivot 的最終位置
}

void quicksort(vector<int>& arr, int left, int right) {
    if(left < right) {
        int pi = partition(arr, left, right);
        quicksort(arr, left, pi - 1);   // 左子陣列
        quicksort(arr, pi + 1, right);  // 右子陣列
    }
}

```

## 6. Couting sort

* 概念：Counting Sort 適用於整數（或可映射為整數）範圍不大的情況，利用額外陣列 count[] 記錄每個數字出現次數。
* 限制：不適用於負數（除非先偏移）。適用範圍：數值小、整數、重複值多時效果好。
* 複雜度：O(n + k)，n為範圍、k為

```cpp
void countingsort(vector<int>& arr) {
    if (arr.empty()) return;

    int maxVal = *max_element(arr.begin(), arr.end());
    int minVal = *min_element(arr.begin(), arr.end());
    int range = maxVal - minVal + 1;

    vector<int> count(range, 0);
    vector<int> output(arr.size());

    // 計數
    for (int num : arr) {
        count[num - minVal]++;
    }

    // 前綴和
    for (int i = 1; i < range; ++i) {
        count[i] += count[i - 1];
    }

    // 穩定排序（從右向左）
    for (int i = arr.size() - 1; i >= 0; --i) {
        output[--count[arr[i] - minVal]] = arr[i];
    }

    arr = output;
}

```

## 7. Radix sort

* 概念：Radix Sort 透過多次 對每一位數字進行穩定排序（通常使用 Counting Sort 作為子程序）來完成排序。例如：對個位數、十位數、百位數…依次排序。
* 通常只適用於 非負整數。必須使用穩定排序作為內部排序方法（如 Counting Sort）。
* 複雜度：O(d × (n + k))，d為位數、n為、k

```cpp
void countSortByDigit(vector<int>& arr, int exp) {
    int N = arr.size();
    vector<int> output(N);
    vector<int> count(10, 0); // 基數為 10

    // 根據目前位數的值做計數
    for (int i = 0; i < N; i++) {
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
    }

    // 前綴和
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // 建立 output 陣列（穩定排序）
    for (int i = N - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[--count[digit]] = arr[i];
    }

    arr = output;
}

void radixsort(vector<int>& arr) {
    if (arr.empty()) return;

    int maxVal = *max_element(arr.begin(), arr.end());

    // 依次針對每個位數排序（1, 10, 100, ...）
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countSortByDigit(arr, exp);
    }
}

```

## 參考資料

1. [C++ std::sort 排序用法與範例完整介紹](https://shengyu7697.github.io/std-sort/)
