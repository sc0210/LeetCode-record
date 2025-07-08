/* 206. Reverse Linked List */
#include "linklist.h"

class Solution
{
public:
    ListNode *reverseList(ListNode *head)
    {
        if (head == nullptr)
            return head;

        ListNode *pre = nullptr;
        ListNode *cur = head;
        ListNode *nxt = head;

        /*
                  1    2    3   4   5   6
            pre<-cur  nxt
                 pre<-cur  nxt
                      pre<-cur  nxt
        */

        while (cur) {
            // preserve
            nxt = cur->next;

            // swap
            cur->next = pre;

            // if(pre==NULL)
            //     cout<<"pre: NULL ";
            // else
            //     cout << "pre: "<< pre->val<<" ";
            // cout<<"cur:"<<cur->val<<" ";
            // if(cur->next==NULL)
            //     cout<<"cur->next: NULL ";
            // else
            //     cout<<"cur->next:"<<cur->next->val<<" ";

            // if(nxt==NULL)
            //     cout<<"nxt: NULL";
            // else
            //     cout << "nxt: "<< nxt->val;
            // cout << endl;

            // iterate
            pre = cur;
            cur = nxt;
        }


        return pre;
    }
};