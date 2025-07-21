#include <stdio.h>

struct ListNode {
    int val;
    struct ListNode *next;

    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}

    void printList()
    {
        ListNode *curr = this;
        while (curr != nullptr) {
            printf("%d", curr->val);
            if (curr->next)
                printf("->");
            curr = curr->next;
        }
        printf("\n");
    }
};
