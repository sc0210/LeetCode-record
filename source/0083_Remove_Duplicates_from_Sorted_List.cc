/* 83. Remove Duplicates from Sorted List */

// #include <unordered_set>
#include "listnode.h"

class Solution
{
public:
    ListNode *deleteDuplicates(ListNode *head)
    {
        // method1
        // if (head == nullptr)
        //     return head;

        // std::unordered_set<int> seen;

        // ListNode dummyhead(0);
        // dummyhead.next = head;

        // ListNode *pre = &dummyhead;
        // ListNode *cur = pre->next;

        // while (cur) {
        //     // add into set when is unique
        //     if (seen.find(cur->val) == seen.end()) {
        //         seen.insert(cur->val);
        //         pre = cur;
        //     } else {
        //         // remove the duplicate node
        //         pre->next = cur->next;
        //     }
        //     // iterate cur pointer
        //     cur = cur->next;
        // }
        // return dummyhead.next;

        // method2: optimal solution
        ListNode *cur = head;
        while (cur && cur->next) {
            if (cur->val == cur->next->val) {
                cur->next = cur->next->next;  // remove duplicate
            } else {
                cur = cur->next;  // move forward
            }
        }
        return head;
    }
};
