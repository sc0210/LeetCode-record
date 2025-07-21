/* 86. Partition List */
#include <stdio.h>
#include <stdlib.h>
#include "listnode.h"

struct ListNode *partition(struct ListNode *head, int x)
{
    struct ListNode less_dummy = {0, NULL};
    struct ListNode more_dummy = {0, NULL};

    struct ListNode *less = &less_dummy;
    struct ListNode *more = &more_dummy;

    while (head) {
        if (head->val < x) {
            less->next = head;
            less = less->next;
        } else {
            more->next = head;
            more = more->next;
        }
        head = head->next;
    }

    more->next = NULL;
    less->next = more_dummy.next;


    return less_dummy.next;
}
