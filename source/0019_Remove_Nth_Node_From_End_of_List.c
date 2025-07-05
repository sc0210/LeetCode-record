/* 19. Remove Nth Node from End of List */
#include <stdio.h>
#include <stdlib.h>
#include "linklist.h"

struct ListNode *removeNthFromEnd(struct ListNode *head, int n)
{
    if (!head)
        return NULL;

    struct ListNode *dummy = malloc(sizeof(struct ListNode));
    dummy->val = 0;
    dummy->next = head;

    struct ListNode *fast = dummy;
    struct ListNode *slow = dummy;

    // make the fast pointer to move ahead of the slow pointer
    for (int i = 0; i < n + 1; i++) {
        if (fast)
            fast = fast->next;
    }
    // move the fast and slow, until the fast pointer reach to the end
    while (fast) {
        fast = fast->next;
        slow = slow->next;
    }

    struct ListNode *to_delete = slow->next;
    slow->next = to_delete->next;
    free(to_delete); /* LeetCode 其實不會檢查，但養成習慣！ */

    return dummy->next;
}

int main(void)
{
    struct ListNode n1_2 = {3, NULL};
    struct ListNode n1_1 = {4, &n1_2};
    struct ListNode n1_0 = {2, &n1_1};
    for (struct ListNode *p = &n1_0; p; p = p->next)
        printf("%d ", p->val);
    printf("\n");

    struct ListNode *removeNode = removeNthFromEnd(&n1_0, 2);
    for (struct ListNode *p = removeNode; p; p = p->next)
        printf("%d ", p->val);
    return 0;
}