#include <math.h>
#include "listnode.h"

// class Solution {
// public:
//     int getDecimalValue(ListNode* head) {
//         ListNode* cur = head;
//         int LENGTH = 0;
//         while(cur){
//             LENGTH++;
//             cur = cur->next;
//         }

//         LENGTH--;
//         int res = 0, i = 0;
//         while(head){
//             res += head->val *pow(2,LENGTH);
//             LENGTH--;
//             head = head->next;
//         }
//         return res;
//     }
// };

class Solution
{
public:
    int getDecimalValue(ListNode *head)
    {
        int res = 0;
        while (head) {
            // Add the current ListNode value
            res += head->val;

            // When traverse to the last ListNode, return res
            if (head->next == NULL)
                break;
            else
                res <<= 1;

            // shift to next ListNode
            head = head->next;
        }
        return res;
    }
};