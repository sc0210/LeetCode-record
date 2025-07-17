/* 141 linked list cycle */
#include "linklist.h"

class Solution {
public:
    bool hasCycle(ListNode *head) {
        // Approach 1
        // Handlde edge case
        // if(head==nullptr) return false;
        // if(head->next==nullptr || head->next->next==nullptr) return false;

        // // At least two node to form cycle
        // ListNode *fast = head->next->next;
        // ListNode *slow = head;
        
        // while(fast->next && fast->next->next){
        //     if(fast->val == slow->val) return true;
        //     else{
        //         slow = slow->next;
        //         fast = fast->next->next;
        //     }
        // }
        // return false;
        
        // Approach 2
        ListNode* fast = head;
        ListNode* slow = head;
        while(fast && fast->next){
            fast = fast->next->next;
            slow = slow->next;
            if(fast == slow) return true;
        }
        return false;
    }
};