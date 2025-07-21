/* 143. Reorder List */

#include "listnode.h"

class Solution
{
public:
    ListNode *reverseList(ListNode *head)
    {
        // When is empty or one node in Linklist, no need for reverse
        if (head == nullptr || head->next == nullptr)
            return head;
        // Reverse process
        ListNode *curr = head;
        ListNode *prev = nullptr;
        while (curr != nullptr) {
            // save nxt
            ListNode *nxt = curr->next;
            // swap
            curr->next = prev;
            // shift
            curr = nxt;
            prev = curr;
        }
        return prev;
    }

    void reorderList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return;

        // step1: Get the middle point by fast-slow pointer
        ListNode *fast = head;
        ListNode *slow = head;
        while (fast != nullptr && fast->next != nullptr) {
            fast = fast->next->next;
            slow = slow->next;
        }

        // step2: Reverse the second half linklist
        ListNode *second = slow->next;  // get the second part linklist
        slow->next = nullptr;           // split the linklist into two part
        second = reverseList(second);

        // step3: Merge two half in alternative
        ListNode *first = head;
        while (second) {
            // save nxt node
            ListNode *tmp1 = first->next;
            ListNode *tmp2 = second->next;
            // reorder
            first->next = second;
            second->next = tmp1;

            first = tmp1;
            second = tmp2;
        }
    }
};