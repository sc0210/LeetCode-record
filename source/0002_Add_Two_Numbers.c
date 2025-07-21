/* 2. Add Two Numbers */
#include <stdio.h>
#include <stdlib.h>
#include "listnode.h"

struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2)
{
    if (l1 == NULL)
        return l2;
    if (l2 == NULL)
        return l1;

    struct ListNode *dummy = malloc(sizeof(struct ListNode));
    dummy->val = 0;
    dummy->next = NULL;
    struct ListNode *curr = dummy;
    int carry = 0, rem;

    while (l1 != NULL || l2 != NULL || carry) {
        int val1 = l1 ? l1->val : 0;
        int val2 = l2 ? l2->val : 0;
        int sum = val1 + val2 + carry;
        rem = sum % 10;
        carry = sum / 10;

        struct ListNode *new_node = malloc(sizeof(struct ListNode));
        new_node->val = rem;
        new_node->next = NULL;

        curr->next = new_node;

        curr = curr->next;
        if (l1)
            l1 = l1->next;
        if (l2)
            l2 = l2->next;
    }
    return dummy->next;
}

int main()
{
    struct ListNode n1_2 = {3, NULL};
    struct ListNode n1_1 = {4, &n1_2};
    struct ListNode n1_0 = {2, &n1_1};
    for (struct ListNode *p = &n1_0; p; p = p->next)
        printf("%d ", p->val);
    printf("\n");

    struct ListNode n0_1 = {4, NULL};
    struct ListNode n0_0 = {6, &n0_1};
    for (struct ListNode *p = &n0_0; p; p = p->next)
        printf("%d ", p->val);
    printf("\n");

    struct ListNode *lists[2] = {&n0_0, &n1_0};

    struct ListNode *merged = addTwoNumbers(&n0_0, &n1_0);
    for (struct ListNode *p = merged; p; p = p->next)
        printf("%d ", p->val);
    return 0;
}