/* 21. Merge Two Sorted Lists */
#include "linklist.h"

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        // handle empty linklist
        if(list1==nullptr) return list2;
        if(list2==nullptr) return list1;

        ListNode dummyHead;
        dummyHead.next = nullptr;
        ListNode *curr = &dummyHead;

        while(list1 && list2){
            if(list1->val <= list2->val){
                curr->next = list1;
                list1 = list1->next;
            }else{
                curr->next = list2;
                list2 = list2->next;
            }
            curr = curr->next;
        }
        if(list1==nullptr) curr->next=list2;
        if(list2==nullptr) curr->next=list1;

        return dummyHead.next;
    }
};