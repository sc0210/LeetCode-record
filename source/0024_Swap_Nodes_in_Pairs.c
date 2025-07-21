/* 24. Swap Nodes in Pairs */
#include <stdio.h>
#include <stdlib.h>
#include "listnode.h"

struct ListNode *swapPairs(struct ListNode *head)
{
    // 0 or 1 node in the linklist
    if (head == NULL || head->next == NULL)
        return head;

    // 2,3,4... nodes in the linklist
    typedef struct ListNode NODE;

    // real dummy node
    NODE dummy;
    dummy.next = head;

    NODE *prev = &dummy;
    NODE *curr = head;

    // when exitsed pair of node to swap
    while (curr && curr->next) {
        NODE *first = curr;
        NODE *second = curr->next;

        // Swapping
        first->next = second->next;
        second->next = first;
        prev->next = second;

        // Move pointers forward
        prev = first;
        curr = first->next;
    }


    return dummy.next;
}