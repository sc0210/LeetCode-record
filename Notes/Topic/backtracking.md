
# 🔁 Backtracking 解題總整理

Backtracking 是一種遞迴策略，用於解決所有可能組合的問題（例如：排列、組合、子集、括號生成、N 皇后等）。

---

## 📌 解題通用模板

```cpp
bool backtrack(參數1, 參數2, ...) {
    // 1. Base case: check if we found a solution
    if (solutionFound(state, step)) {
        recordSolution(state);
        return true/false; // depending on problem
    }

    // 2. Iterate over all choices
    for (choice in allChoices) {
        if (isValid(choice, state)) {
            // 2.1 Make the choice
            makeChoice(state, choice);

            // 2.2 Recurse 遞迴檢查其他可能
            if (backtrack(state, step+1, ...)) {
                // sometimes return true immediately if only one solution is needed
            }

            // 2.3 Undo the choice (backtrack) 回溯
            undoChoice(state, choice);
        }
    }
    return false; // no solution found in this branch
}
```

---

## 🎯 經典題型與範例

### 1. 括號生成（Generate Parentheses）

- 題號：[LeetCode 22. Generate Parentheses](https://leetcode.com/problems/generate-parentheses/description/)
- 類型：組合 + 有效性檢查

```cpp
void backtrack(string path, int left, int right, int n) {
    if (path.size() == 2 * n) {
        res.push_back(path);
        return;
    }

    if (left < n) backtrack(path + '(', left + 1, right, n);
    if (right < left) backtrack(path + ')', left, right + 1, n);
}
```

---

### 2. 子集（Subsets）

- 題號：[LeetCode 78. Subsets](https://leetcode.com/problems/subsets/)
- 類型：組合（每個元素選或不選）

```cpp
void backtrack(vector<int>& nums, int start, vector<int>& path) {
    res.push_back(path);
    for (int i = start; i < nums.size(); ++i) {
        path.push_back(nums[i]);
        backtrack(nums, i + 1, path);
        path.pop_back();
    }
}
```

---

### 3. 排列（Permutations）

- 題號：[LeetCode 46. Permutations](https://leetcode.com/problems/permutations/)
- 類型：全排列 + 訪問控制

```cpp
void backtrack(vector<int>& nums, vector<bool>& used, vector<int>& path) {
    if (path.size() == nums.size()) {
        res.push_back(path);
        return;
    }
    for (int i = 0; i < nums.size(); ++i) {
        if (used[i]) continue;
        used[i] = true;
        path.push_back(nums[i]);
        backtrack(nums, used, path);
        path.pop_back();
        used[i] = false;
    }
}
```

---

### 4. 組合總和（Combination Sum）

- 題號：[LeetCode 39. Combination Sum](https://leetcode.com/problems/combination-sum/)
- 類型：組合 + 剪枝

```cpp
void backtrack(vector<int>& candidates, int target, int start, vector<int>& path) {
    if (target == 0) {
        res.push_back(path);
        return;
    }
    for (int i = start; i < candidates.size(); ++i) {
        if (target < candidates[i]) continue;
        path.push_back(candidates[i]);
        backtrack(candidates, target - candidates[i], i, path);
        path.pop_back();
    }
}
```

---

### 5. N 皇后（N-Queens）

- 題號：[LeetCode 51. N-Queens](https://leetcode.com/problems/n-queens/)
- 類型：排列 + 合法性檢查

```cpp
bool isValid(vector<string>& board, int row, int col, int n) {
    for (int i = 0; i < row; ++i)
        if (board[i][col] == 'Q') return false;

    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j)
        if (board[i][j] == 'Q') return false;

    for (int i = row - 1, j = col + 1; i >= 0 && j < n; --i, ++j)
        if (board[i][j] == 'Q') return false;

    return true;
}

void backtrack(vector<string>& board, int row, int n) {
    if (row == n) {
        res.push_back(board);
        return;
    }
    for (int col = 0; col < n; ++col) {
        if (!isValid(board, row, col, n)) continue;
        board[row][col] = 'Q';
        backtrack(board, row + 1, n);
        board[row][col] = '.';
    }
}
```

### 6. 單詞搜尋（Word Search）

- 題號：[LeetCode 79. Word Search](https://leetcode.com/problems/word-search/)
- 類型：DFS + 回溯 + 網格搜尋

```cpp
bool dfs(vector<vector<char>>& board, string& word, int r, int c, int i) {
    if (i == word.size()) return true;
    if (r < 0 || c < 0 || r >= board.size() || c >= board[0].size() || board[r][c] != word[i])
        return false;

    char tmp = board[r][c];
    board[r][c] = '#'; // 標記為已訪問

    bool found = dfs(board, word, r+1, c, i+1) ||
                 dfs(board, word, r-1, c, i+1) ||
                 dfs(board, word, r, c+1, i+1) ||
                 dfs(board, word, r, c-1, i+1);

    board[r][c] = tmp; // 回溯，恢復狀態
    return found;
}
```

---

## 🧠 解題技巧總結

| 技巧      | 說明                                               |
| ------- | ------------------------------------------------ |
| 遞迴 + 回溯 | 每一層遞迴處理一個選擇點                                     |
| 合法性剪枝   | 在嘗試遞迴前檢查條件                                       |
| 狀態回復    | 遞迴後撤銷操作（例如 `pop_back`, `used[i] = false`，或恢復棋盤格） |
| 路徑記錄    | 用 `path` 或 `track` 記錄當前的選擇                       |

## 📋 常見題型對照表

| 題型          | 要決定什麼？     | 遞迴參數包含什麼？                         | 特殊處理            |
| ----------- | ---------- | --------------------------------- | --------------- |
| Permutation | 下一個要放哪個數？  | path, visited\[], 或 in-place swap | 判斷是否用過          |
| Combination | 從哪個數開始挑？   | path, start index                 | 避免重複            |
| Subset      | 是否選擇這個數？   | path, start index                 | 不用判重            |
| 括號生成        | 加 ( 還是 )？  | 當前字串、剩下的左右括號數                     | `left <= right` |
| N 皇后        | 每列放哪個 col？ | row、使用中的 cols/diag1/diag2         | 判斷衝突            |
| 迷宮/網格       | 下一步走哪裡？    | i, j, 當前字串 index, visited\[]\[]   | DFS 方向與還原       |
| 單詞搜尋        | 下一個字母在哪？   | row, col, index, board            | 記得恢復格子狀態        |
