/* 147. Insertion Sort List */
#include "listnode.h"

class Solution
{
public:
    ListNode *insertionSortList(ListNode *head)
    {
        ListNode dummyHead;
        ListNode *cur = head;

        while (cur != nullptr) {
            ListNode *prev = &dummyHead;
            // find the position the insert current node
            while (prev->next != nullptr && prev->next->val <= cur->val) {
                prev = prev->next;
            }

            ListNode *nxt = cur->next;
            // Insert the current node to the new list
            cur->next = prev->next;
            prev->next = cur;
            // moving on to the next iteration
            cur = nxt;
        }
        return dummyHead.next;
    }
};