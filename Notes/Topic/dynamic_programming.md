# 💡 動態規劃（Dynamic Programming）學習筆記

動態規劃（DP）是一種用於求解「最優化問題」的技巧，它透過儲存子問題的結果，避免重複計算，提升效率。

---

## 📌 動態規劃解題五步驟

1. **定義狀態（State）**  
   定義 `dp[i]` 的意義，例如：「前 i 個元素的最大值」、「到達第 i 個台階的方法數」等。

2. **決策選項（Choice）**  
   每一步可以做哪些選擇？如選/不選、跳一格/跳兩格、拿/不拿等。

3. **狀態轉移方程（Transition Function）**  
   根據子問題的結果推導出當前狀態的值。

4. **初始條件（Base Case）**  
   通常是最簡單的邊界狀況，如 `dp[0]`、`dp[1]` 等。

5. **最終答案（Answer）**  
   `dp[n]` 或整個 dp 陣列中的最大值等，依問題而定。

## 做法：

- Top-Down = recursion + memoization.
- Bottom-Up = iterative filling of DP table.

## ✅ 範例一：Maximum Subarray（最大子陣列和）

### 題目：

給定一個整數陣列，找出具有最大和的連續子陣列。

### 思路：

Kadane’s Algorithm。對每個位置 i，決定是否延續前一個子陣列，還是從 i 重新開始。

### 狀態定義：

- `dp[i]` 表示「以第 i 個元素結尾」的最大子陣列和

### 狀態轉移方程：

```cpp
dp[i] = max(nums[i], dp[i - 1] + nums[i])
```

### 初始條件：

```cpp
dp[0] = nums[0]
```

### C++ 程式碼（簡化版本）：

```cpp
int maxSubArray(vector<int>& nums) {
    int maxSum = nums[0];
    int currentSum = nums[0];
    for (int i = 1; i < nums.size(); ++i) {
        currentSum = max(nums[i], currentSum + nums[i]);
        maxSum = max(maxSum, currentSum);
    }
    return maxSum;
}
```

---

## ✅ 範例二：Climbing Stairs（爬樓梯）

### 題目：

每次可以爬 1 或 2 階，問爬到第 n 階有幾種方式。

### 狀態定義：

- `dp[i]` 表示爬到第 i 階的方法數

### 狀態轉移方程：

```cpp
dp[i] = dp[i - 1] + dp[i - 2]
```

### 初始條件:

```cpp
dp[0] = 1
dp[1] = 1
```

### C++ 程式碼：

```cpp
int climbStairs(int n) {
    if (n <= 1) return 1;
    vector<int> dp(n + 1);
    dp[0] = dp[1] = 1;
    for (int i = 2; i <= n; ++i) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}
```

---

## ✅ 範例三：0/1 背包問題

### 題目：

給定重量與價值陣列、總容量，找出最大可裝載價值。

### 狀態定義：

- `dp[i][w]` 表示「前 i 個物品、容量為 w」的最大價值。

### 狀態轉移方程：

```cpp
if (w >= weight[i])
    dp[i][w] = max(dp[i-1][w], dp[i-1][w - weight[i]] + value[i]);
else
    dp[i][w] = dp[i-1][w];
```

---

## 🧠 小技巧 & 注意事項

- 可以用 **一維陣列** 優化空間，通常是從後往前更新。
- 記得考慮 **邊界條件 / base case**。
- **Traceback** 可用來還原選擇路徑（例如列出選了哪些物品）。
- 遇到子問題重疊，可優先考慮 DP。

---

## 📚 推薦練習題目（LeetCode）

| 題目 | 類型 |
|------|------|
| [53. Maximum Subarray](https://leetcode.com/problems/maximum-subarray/) | 基礎 |
| [70. Climbing Stairs](https://leetcode.com/problems/climbing-stairs/description/) | 基礎 |
| [198. House Robber](https://leetcode.com/problems/house-robber/description/) | 線性狀態轉移 |
| [322. Coin Change](https://leetcode.com/problems/coin-change/description/) | 完全背包 |
| [1143. Longest Common Subsequence](https://leetcode.com/problems/longest-common-subsequence/description/) | 二維 DP |
| [72. Edit Distance](https://leetcode.com/problems/edit-distance/description/) | 字串編輯距離 |
| [300. Longest Increasing Subsequence](https://leetcode.com/problems/longest-increasing-subsequence/description/) | LIS |
| [518. Coin Change II](https://leetcode.com/problems/coin-change-ii/description/) | 完全背包變形 |

---