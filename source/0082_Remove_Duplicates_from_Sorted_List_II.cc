/* 82. Remove Duplicates from Sorted List II */

#include "listnode.h"

class Solution
{
public:
    ListNode *deleteDuplicates(ListNode *head)
    {
        ListNode dummy(0);
        dummy.next = head;
        ListNode *prev = &dummy;

        while (head) {
            // when found duplicate
            if (head->next && head->val == head->next->val) {
                int duplicateVal = head->val;
                // shift the head pointer to next non-duplicate val
                while (head && head->val == duplicateVal) {
                    head = head->next;
                }
                // link the prev poiner to next non-duplicate node
                prev->next = head;
            } else {
                // iterate to next round
                prev = head;
                head = head->next;
            }
        }

        return dummy.next;
    }
};