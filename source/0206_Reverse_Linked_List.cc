/* 206. Reverse Linked List */
#include "linklist.h"

/*
          1    2    3   4   5   
    pre<-cur  nxt
         pre<-cur  nxt
              pre<-cur  nxt
*/

class Solution
{
public:
    ListNode *reverseList(ListNode *head)
    {
        if (head == nullptr)
            return head;

        ListNode *pre = nullptr;
        ListNode *cur = head;

        

        while (cur) {
            // preserve nxt node
            ListNode *nxt = cur->next;
            
            // swap
            cur->next = pre;

            // iterate
            pre = cur;
            cur = nxt;
        }


        return pre;
    }
};