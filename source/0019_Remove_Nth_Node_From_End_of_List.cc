/* 19. Remove Nth Node From End of List */

#include "listnode.h"

class Solution
{
public:
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        // only one node in the linklist
        if (n == 1 && head->next == nullptr)
            return nullptr;

        // fast slow pointer, fast need to be ahead of slow n steps
        ListNode *fast = head;
        ListNode *slow = head;

        for (int i = 0; i < n; i++) {
            fast = fast->next;
            if (fast == nullptr) {
                // when n is equal to the size of linklist
                // remove the head of the linklist, return head->next;
                ListNode *nxt = head->next;
                head->next = nullptr;
                return nxt;
            }
        }

        // else, let the fast pointer to the end
        while (fast->next != nullptr) {
            fast = fast->next;
            slow = slow->next;
        }
        // remove target (slow->next)
        slow->next = slow->next->next;
        return head;
    }
};