/* 21. Merge Two Sorted Lists */
#include <stdio.h>
#include <stdlib.h>
#include "linklist.h"

struct ListNode *mergeTwoLists(struct ListNode *list1, struct ListNode *list2)
{
    if (list1 == NULL)
        return list2;
    if (list2 == NULL)
        return list1;

    // struct ListNode * curr = malloc(sizeof(struct ListNode));
    // curr->next = NULL;
    // curr->val = 0;
    // struct ListNode * dummy = curr;

    // while(list1!=NULL && list2!=NULL){
    //     if(list1->val <= list2->val){
    //         curr->next = list1;
    //         list1 = list1->next;
    //         curr = curr->next;
    //     }else{
    //         curr->next = list2;
    //         list2 = list2->next;
    //         curr = curr->next;
    //     }
    // }
    // if(list1) curr->next = list1;
    // if(list2) curr->next = list2;
    // return dummy->next;

    struct ListNode res;
    res.next = NULL;
    struct ListNode *ptr = &res;

    while (list1 != NULL && list2 != NULL) {
        if (list1->val <= list2->val) {
            ptr->next = list1;
            list1 = list1->next;
        } else {
            ptr->next = list2;
            list2 = list2->next;
        }
        ptr = ptr->next;
    }
    if (list1)
        ptr->next = list1;
    if (list2)
        ptr->next = list2;
    return res.next;
}

int main(void)
{
    struct ListNode n1_2 = {5, NULL};
    struct ListNode n1_1 = {4, &n1_2};
    struct ListNode n1_0 = {1, &n1_1};

    struct ListNode n0_1 = {1, NULL};
    struct ListNode n0_0 = {0, &n0_1};

    struct ListNode *lists[2] = {&n0_0, &n1_0};

    struct ListNode *merged = mergeTwoLists(&n0_0, &n1_0);
    for (struct ListNode *p = merged; p; p = p->next)
        printf("%d ", p->val);
    return 0;
}