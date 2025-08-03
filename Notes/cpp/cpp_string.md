# C++ string

## 1. 基本操作

### 1-1. 長度與索引

```cpp
std::string s = "hello world";
size_t n = s.size();    // 11
char c = s[1];          // 'e'
s[0] = 'H';             // "Hello world"
```

### 1-2. 子字串與搜尋／取代

```cpp
std::string file = "/home/main.cpp";
auto name = file.substr(file.find_last_of('/') + 1); // "main.cpp"

std::string txt = "one fish two fish";
auto p = txt.find("fish");  // 4
txt.replace(p, 4, "cat");   // "one cat two fish"
```

### 1-3. 前後綴檢查（C++20）

```cpp
if (s.starts_with("Hel") && s.ends_with("world")) {
    /* ... */
}
```

---

## 2. 分割 (Split)

### 2-1. 手動 `find`（效能佳）

```cpp
std::vector<std::string> split_manual(const std::string& s, char delim) {
    std::vector<std::string> out;
    size_t start = 0, end;
    while ((end = s.find(delim, start)) != std::string::npos) {
        out.emplace_back(s.substr(start, end - start));
        start = end + 1;
    }
    out.emplace_back(s.substr(start));
    return out;
}
```

### 2-2. `stringstream`（語意簡潔）

```cpp
std::vector<std::string> split_stream(const std::string& s, char delim) {
    std::vector<std::string> out;
    std::string part;
    std::istringstream iss(s);
    while (std::getline(iss, part, delim)) out.push_back(part);
    if (!s.empty() && s.back() == delim) out.emplace_back(""); // 與手動版行為一致
    return out;
}
```

---

## 3. 轉型與拼接

```cpp
int num   = std::stoi("42");
double pi = std::stod("3.14");
std::string s = std::to_string(42);

std::string a = "Hello", b = "world";
std::string joined = a + " " + b;

std::ostringstream oss;
oss << "val=" << 10 << ", pi=" << pi;
auto msg = oss.str();
```

---

## 4. 清理與字符工具

### 4-1. Trim 空白

```cpp
std::string trim(std::string s) {
    s.erase(0,  s.find_first_not_of(" \t\r\n"));
    s.erase(    s.find_last_not_of(" \t\r\n") + 1);
    return s;
}
```

### 4-2. 字符判定／轉換

```cpp
char ch = 'a';
std::isalpha(ch); // 字母？
std::isdigit(ch); // 數字？
std::toupper(ch); // 'A'
std::tolower(ch); // 'a'
```

---

## 5. 進階技巧與面試重點

### 5-1. `std::string_view`（C++17 起）

```cpp
std::string_view sv = "abc:def:ghi";
auto pos = sv.find(':');
auto first = sv.substr(0, pos); // "abc"（無複製）
```

### 5-2. 多重分割（多個分隔符）

```cpp
std::vector<std::string> multi_split(const std::string& s, const std::string& delims) {
    std::vector<std::string> result;
    size_t start = 0;
    while (start < s.size()) {
        size_t pos = s.find_first_of(delims, start);
        if (pos == std::string::npos) pos = s.size();
        if (pos > start) result.push_back(s.substr(start, pos - start));
        start = pos + 1;
    }
    return result;
}
```

### 5-3. 字串反轉與旋轉

```cpp
std::string s = "abcdef";
std::reverse(s.begin(), s.end()); // "fedcba"
std::rotate(s.begin(), s.begin() + 2, s.end()); // "cdefab"
```

### 5-4. 字元頻率統計

```cpp
std::array<int, 256> freq = {};
for (char c : s) freq[c]++;
```

### 5-5. 常見面試題型與 LeetCode 連結

| 題目                           | 題號   | 技巧             | LeetCode                                                                                | C++ 解法骨架                                           |
| ---------------------------- | ---- | -------------- | --------------------------------------------------------------------------------------- | -------------------------------------------------- |
| Valid Palindrome             | 125  | 雙指標、判斷         | [🔗](https://leetcode.com/problems/valid-palindrome/)                                   | `bool isPalindrome(string s)`                      |
| strStr (實作 find)             | 28   | 模擬 / KMP       | [🔗](https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/) | `int strStr(string haystack, string needle)`       |
| Anagram 判斷                   | 242  | 排序 / hashmap   | [🔗](https://leetcode.com/problems/valid-anagram/)                                      | `bool isAnagram(string s, string t)`               |
| Longest Common Prefix        | 14   | 遞減比較           | [🔗](https://leetcode.com/problems/longest-common-prefix/)                              | `string longestCommonPrefix(vector<string>& strs)` |
| Atoi 實作                      | 8    | 邊界處理           | [🔗](https://leetcode.com/problems/string-to-integer-atoi/)                             | `int myAtoi(string s)`                             |
| Remove Adjacent Duplicates   | 1047 | stack          | [🔗](https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string/)           | `string removeDuplicates(string s)`                |
| Decode String                | 394  | stack 模擬遞迴     | [🔗](https://leetcode.com/problems/decode-string/)                                      | `string decodeString(string s)`                    |
| Minimum Window Substring     | 76   | sliding window | [🔗](https://leetcode.com/problems/minimum-window-substring/)                           | `string minWindow(string s, string t)`             |
| Longest Substring w/o Repeat | 3    | sliding window | [🔗](https://leetcode.com/problems/longest-substring-without-repeating-characters/)     | `int lengthOfLongestSubstring(string s)`           |

📚 LeetCode 題單推薦：

* [🔥 字串技巧刷題清單 (LeetCode curated)](https://leetcode.com/problem-list/top-interview-questions/) → 可手動建立個人題單標記常見字串類型

---

## 6. 附錄

| 特性    | `std::string`             | C 字串 (`char*`)   |
| ----- | ------------------------- | ---------------- |
| 記憶體管理 | 自動                        | 手動 (malloc)      |
| 安全性   | 有邊界檢查                     | 易越界              |
| 功能豐富  | find / replace / substr 等 | 需 `<cstring>` 補齊 |

**常用標頭**

```cpp
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <array>
#include <string_view>
```
