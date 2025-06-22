/*  Definition for singly-linked list. */
#include <stdio.h>
#include <stdlib.h>
#include "linklist.h"

/* 23. Merge k Sorted Lists */
struct ListNode *mergeTwo(struct ListNode *l1, struct ListNode *l2)
{
    if (l1 == NULL)
        return l2;
    if (l2 == NULL)
        return l1;

    struct ListNode res = {0, NULL};
    struct ListNode *ptr = &res;

    // struct ListNode res;
    // res.next = NULL;
    // struct ListNode * ptr = &res;

    while (l1 && l2) {
        if (l1->val <= l2->val) {
            ptr->next = l1;
            l1 = l1->next;
            ptr = ptr->next;
        } else {
            ptr->next = l2;
            l2 = l2->next;
            ptr = ptr->next;
        }
    }
    ptr->next = l1 ? l1 : l2;
    // if(l1!=NULL) ptr->next = l1;
    // if(l2!=NULL) ptr->next = l2;

    return res.next;
}

struct ListNode *mergeKLists(struct ListNode **lists, int listsSize)
{
    if (listsSize == 0)
        return NULL;
    if (listsSize == 1)
        return lists[0];

    while (listsSize > 1) {
        int i = 0;
        for (; i < listsSize / 2; ++i) {
            lists[i] = mergeTwo(lists[i], lists[listsSize - 1 - i]);
        }
        listsSize = (listsSize + 1) / 2;  // handle odd case
    }
    return lists[0];
}

// struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
//     // merge the list by two
//     struct ListNode * res = malloc(sizeof(struct ListNode));
//     res->next = NULL;

//     for(int listIndex = 1; listIndex <= listsSize; listIndex+=2){
//         // merger two list
//         struct ListNode * targetList = lists[listIndex];
//         res = mergeTwo(res, targetList);
//     }
//     if(listsSize%2!=0){
//         // there will still have a list left
//         res = mergeTwo(res, lists[listsSize-1]);
//     }
//     return res;
// }

int main(void)
{
    struct ListNode n1_2 = {5, NULL};
    struct ListNode n1_1 = {4, &n1_2};
    struct ListNode n1_0 = {1, &n1_1};

    struct ListNode n0_1 = {1, NULL};
    struct ListNode n0_0 = {0, &n0_1};

    struct ListNode *lists[2] = {&n0_0, &n1_0};

    struct ListNode *merged = mergeKLists(lists, 2);
    for (struct ListNode *p = merged; p; p = p->next)
        printf("%d ", p->val);
    return 0;
}