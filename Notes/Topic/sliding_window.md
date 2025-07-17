# 🧊 Sliding Window 技巧總整理

滑動視窗（Sliding Window）是一種高效處理陣列/字串中「連續子區段」問題的技巧。

---

## 📌 適用時機

- 對字串或陣列的**子陣列/子字串區段**進行操作
- 找**最長/最短/符合條件的區段**
- 固定或可變視窗大小，**逐步更新統計資訊**

---

## 🎯 兩種 Sliding Window 模板

### 1️⃣ 固定長度視窗（Fixed Window）

適合題型：
- 長度為 K 的子陣列總和、平均
- 是否存在 permutation（字元出現次數相同）

**模板：**
```cpp
for (int i = 0; i < k; i++) {
    // 初始化第一個視窗
}
for (int r = k; r < s.length(); r++) {
    // 加入 s[r] 右邊元素
    // 移除 s[l] 左邊元素
    // l++
    // 判斷目前視窗是否合法
}
```

**常見工具：**
- `vector<int> count(26)`：字母頻率
- `int sum`：區段總和

---

### 2️⃣ 可變長度視窗（Dynamic Window）

適合題型：
- 找最短/最長滿足條件的區段
- 元素出現不重複
- 滿足某個總和條件

**模板：**
```cpp
int l = 0;
for (int r = 0; r < s.length(); r++) {
    // 擴展右邊 r，加進視窗統計

    while (視窗不合法) {
        // 縮小左邊 l，直到合法
        l++;
    }

    // 更新答案（最長 / 最短）
}
```

**常見工具：**
- `unordered_map<char, int>`：字元計數
- `unordered_set<char>`：是否重複
- `int sum`：目前總和

---

## 🧪 常見題型與範例

| 題型 | 題目連結 | 關鍵技巧 |
|------|----------|-----------|
| ✅ 固定長度 permutation | [567. Permutation in String](https://leetcode.com/problems/permutation-in-string/) | 頻率比對 + match counter |
| ✅ 最大總和子陣列（長度 K） | [643. Maximum Average Subarray I](https://leetcode.com/problems/maximum-average-subarray-i/) | 總和維護 |
| ✅ 最短子陣列 >= target | [209. Minimum Size Subarray Sum](https://leetcode.com/problems/minimum-size-subarray-sum/) | 可變視窗 + sum |
| ✅ 最長不重複子字串 | [3. Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/) | `unordered_set` 去重 |
| ✅ 滿足所有字母 | [76. Minimum Window Substring](https://leetcode.com/problems/minimum-window-substring/) | `map<char,int>` + match count |
| ✅ 替換字元求最長 | [424. Longest Repeating Character Replacement](https://leetcode.com/problems/longest-repeating-character-replacement/) | 保持最多字元頻率 |

---

## 📚 小技巧彙整

- `s[l++]`：移除左邊
- `s[r++]`：加入右邊
- `match++ / match--`：用於精準記錄符合條件的字母種類
- `if (s1Count == s2Count)`：可以用來比對整體頻率是否相等（但效能略低）

---

## 🔚 總結表格

| 類型 | 典型題目 | 視窗調整 | 工具 |
|------|-----------|------------|------|
| 固定長度 | permutation、平均值 | 固定 k | 頻率、總和 |
| 可變長度 | 無重複、滿足條件 | 動態調整 | set, map, sum |