/* 148. Sort List */
#include "listnode.h"

class Solution
{
public:
    ListNode *sortList(ListNode *head)
    {
        if (!head || !head->next)
            return head;

        // Get length
        int length = 0;
        ListNode *node = head;
        while (node) {
            length++;
            node = node->next;
        }

        /* Bottom-Up Merge Sort, spaceO(1), time(NlogN)
         * Merge size: 1, 2, 4, 8 ...
         */
        ListNode dummy(0, head);
        for (int step = 1; step < length; step *= 2) {
            ListNode *prev = &dummy;
            ListNode *curr = dummy.next;

            while (curr) {
                ListNode *left = curr;
                ListNode *right = split(left, step);
                curr = split(right, step);

                prev = merge(left, right, prev);
            }
        }
        return dummy.next;
    }

private:
    // Split the list into two parts, return the head of second part
    ListNode *split(ListNode *head, int n)
    {
        while (--n && head)
            head = head->next;
        if (!head)
            return nullptr;

        ListNode *second = head->next;
        head->next = nullptr;
        return second;
    }

    // Merge two sorted lists, append result to prev->next
    // Return the tail of the merged list
    ListNode *merge(ListNode *l1, ListNode *l2, ListNode *prev)
    {
        ListNode *curr = prev;
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
        curr->next = (l1 ? l1 : l2);
        while (curr->next)
            curr = curr->next;
        return curr;
    }
};
