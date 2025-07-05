/* 61. Rotate List */
#include <stdio.h>
#include <stdlib.h>
#include "linklist.h"

struct ListNode *rotateRight(struct ListNode *head, int k)
{
    if (head == NULL)
        return head;

    typedef struct ListNode NODE;
    NODE *curr = head;

    NODE dummy;
    dummy.next = head;

    // traverse all the node
    int SIZE = 0;
    while (curr) {
        SIZE++;
        curr = curr->next;
    }

    // if k exceed SIZE, then get the remanider value
    k %= SIZE;
    if (k == 0)
        return head;

    // apply fast-slow pointer
    // fast pointer move k steps more than slow poiner
    NODE *fast = head, *slow = head;
    for (int i = 0; i < k; i++) {
        fast = fast->next;
    }
    while (fast->next != NULL) {
        slow = slow->next;
        fast = fast->next;
    }

    dummy.next = slow->next;
    fast->next = head;
    slow->next = NULL;

    return dummy.next;
}