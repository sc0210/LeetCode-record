/* 2. Add Two Number */
#include "listnode.h"

class Solution
{
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        int carry = 0;
        ListNode dummyHead;
        ListNode *ptr = &dummyHead;

        while (l1 != nullptr || l2 != nullptr || carry) {
            int val1 = (l1 != nullptr) ? l1->val : 0;
            int val2 = (l2 != nullptr) ? l2->val : 0;
            int sum = val1 + val2 + carry;
            carry = sum / 10;
            // create new node
            ListNode *newNode = new ListNode(sum % 10);
            ptr->next = newNode;
            // shift
            ptr = ptr->next;
            if (l1)
                l1 = l1->next;
            if (l2)
                l2 = l2->next;
        }
        return dummyHead.next;
    }
};