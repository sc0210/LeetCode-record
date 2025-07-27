/* 203. Remove Linked List Elements */

#include "listnode.h"

class Solution
{
public:
    ListNode *removeElements(ListNode *head, int val)
    {
        if (head == nullptr)
            return head;

        // create dummy head;
        ListNode dummyhead(0);
        dummyhead.next = head;

        ListNode *pre = &dummyhead;
        ListNode *cur = pre->next;  // head

        while (cur) {
            if (cur->val == val) {
                // cur == val, modify pre next pointer
                pre->next = cur->next;
                ListNode *tmp = cur;
                cur = cur->next;
                delete tmp;  // release memory
            } else {
                // cur != val, iterate pre pointer
                pre = cur;
                cur = cur->next;
            }
        }
        return dummyhead.next;
    }
};