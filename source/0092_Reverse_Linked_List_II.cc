/* 92. Reverse Linked List II */

#include "listnode.h"

/*
     1    2    3    4   5   6
    pre<-cur  nxt
         pre<-cur nxt
              pre<-cur  nxt
*/

class Solution
{
public:
    ListNode *reverseBetween(ListNode *head, int left, int right)
    {
        if (!head || left == right) {
            return head;
        }

        ListNode dummy;
        dummy.next = head;
        ListNode *prev = &dummy;

        for (int i = 0; i < left - 1; i++) {
            prev = prev->next;
        }

        ListNode *cur = prev->next;

        for (int i = 0; i < right - left; i++) {
            // preseve next node
            ListNode *nxt = cur->next;
            // reverse link
            cur->next = nxt->next;
            nxt->next = prev->next;
            prev->next = nxt;
        }
        return dummy.next;
    }
};