/* 148. Sort List */
#include <stdio.h>
#include <stdlib.h>
// #include "listnode.h"

// Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode *next;
};

// Utility: create new node
struct ListNode *createNode(int val)
{
    struct ListNode *node = (struct ListNode *) malloc(sizeof(struct ListNode));
    node->val = val;
    node->next = NULL;
    return node;
}

// Merge two sorted lists
struct ListNode *merge(struct ListNode *l1, struct ListNode *l2)
{
    struct ListNode dummy;
    struct ListNode *tail = &dummy;
    dummy.next = NULL;

    while (l1 && l2) {
        if (l1->val < l2->val) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }

    tail->next = (l1 ? l1 : l2);
    return dummy.next;
}

// Split list into two halves
void split(struct ListNode *head,
           struct ListNode **left,
           struct ListNode **right)
{
    struct ListNode *slow = head;
    struct ListNode *fast = head;
    struct ListNode *prev = NULL;

    while (fast && fast->next) {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }

    // Break the list into two
    if (prev)
        prev->next = NULL;
    *left = head;
    *right = slow;
}

// Merge Sort
struct ListNode *sortList(struct ListNode *head)
{
    if (!head || !head->next)
        return head;

    struct ListNode *left;
    struct ListNode *right;

    split(head, &left, &right);
    left = sortList(left);
    right = sortList(right);

    return merge(left, right);
}
