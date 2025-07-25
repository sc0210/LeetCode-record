# Bottom-Up Merge Sort template (Linked List)

```cpp
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if (!head || !head->next) return head;

        // Step 1: 計算 list 長度
        int length = 0;
        ListNode* node = head;
        while (node) {
            length++;
            node = node->next;
        }

        // Step 2: 使用 dummy node 幫助處理 head
        ListNode dummy(0, head);

        // Step 3: 自底向上進行 merge，每次 merge 的區段長度為 step（1, 2, 4, 8...）
        for (int step = 1; step < length; step *= 2) {
            ListNode* prev = &dummy;
            ListNode* curr = dummy.next;

            while (curr) {
                // 取得兩段分組 head
                ListNode* left = curr;
                ListNode* right = split(left, step);
                curr = split(right, step);

                // 合併並更新 prev 位置
                prev = merge(left, right, prev);
            }
        }

        return dummy.next;
    }

private:
    // split: 將 list 從 head 開始，分成長度為 n 的子串，並回傳下一段的開頭
    ListNode* split(ListNode* head, int n) {
        while (--n && head)
            head = head->next;
        if (!head) return nullptr;

        ListNode* second = head->next;
        head->next = nullptr;
        return second;
    }

    // merge: 合併兩段 sorted list，接在 prev 後，並返回新的 tail 節點
    ListNode* merge(ListNode* l1, ListNode* l2, ListNode* prev) {
        ListNode* curr = prev;
        while (l1 && l2) {
            if (l1->val < l2->val) {
                curr->next = l1;
                l1 = l1->next;
            } else {
                curr->next = l2;
                l2 = l2->next;
            }
            curr = curr->next;
        }

        curr->next = (l1) ? l1 : l2;

        // 移動到 tail 節點，準備接續下一段
        while (curr->next) curr = curr->next;
        return curr;
    }
};
```

---

## 模板重點流程圖

```cpp
for (step = 1; step < len; step *= 2):
    curr = head
    while curr:
        left  = curr
        right = split(left, step)
        curr  = split(right, step)
        prev  = merge(left, right, prev)
```

---

## 模板應用情境

這種 bottom-up merge sort 模板可以應用在：

- sortList 鏈結串列排序（[Leetcode 148. Sort List](https://leetcode.com/problems/sort-list/description/)）
- 合併排序操作但無法使用遞迴的情境（如 embedded）
- 空間敏感問題（因為是 O(1) 空間）

---

# Top-Down Merge Sort template (Linked List)

核心思路:

- 利用 快慢指標 找出鏈表中點，把鏈表拆成兩半。
- 分別遞迴排序左右兩半。
- 合併兩個已排序的鏈表。

## C++ 範例模板
```cpp
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        // base case：空串列或單節點
        if (!head || !head->next) return head;

        // 找中點並斷開鏈表
        ListNode* mid = getMid(head);

        // 遞迴拆解
        ListNode* left = sortList(head);
        ListNode* right = sortList(mid);

        // 合併兩已排序鏈表
        return merge(left, right);
    }

private:
    // 找鏈表中點並斷開鏈表
    ListNode* getMid(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        ListNode* prev = nullptr;

        while (fast && fast->next) {
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        // 斷開鏈表，分成兩半
        if (prev) prev->next = nullptr;

        return slow;
    }

    // 合併兩個排序好的鏈表
    ListNode* merge(ListNode* l1, ListNode* l2) {
        ListNode dummy;
        ListNode* tail = &dummy;

        while (l1 && l2) {
            if (l1->val < l2->val) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }

        tail->next = l1 ? l1 : l2;
        return dummy.next;
    }
};
```

## 複雜度分析

| 參數 | 複雜度            |
| -- | -------------- |
| 時間 | O(n log n)     |
| 空間 | O(log n) (遞迴棧) |

## 適用場景

- 題目沒有空間限制，想法直覺且實作簡單。
- 對於中小規模資料，遞迴深度不會造成 stack overflow。
