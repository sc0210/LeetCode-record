/* 100. Same Tree */

#include "treenode.h"

class Solution
{
public:
    bool isSameTree(TreeNode *p, TreeNode *q)
    {
        // // Both are NULL, return true
        // if (p == nullptr && q == nullptr) {
        //     return true;
        // }
        // // existed one is NULL, return false
        // if ((p == nullptr && q != nullptr) || (p != nullptr && q == nullptr))
        // {
        //     return false;
        // }
        // // Both have value, check if it equal
        // if (p->val != q->val) {
        //     return false;
        // }
        // // recursive to check the left and rigth subtree
        // return (isSameTree(p->left, q->left) && isSameTree(p->right,
        // q->right));

        // When both are is nullptr, return true
        if (p == nullptr && q == nullptr) {
            return true;
        }
        // When both are not nullptr, compare the value
        // recursive check left and right subtree
        if (p != nullptr && q != nullptr && p->val == q->val) {
            return isSameTree(p->left, q->left) &&
                   isSameTree(p->right, q->right);
        } else {
            return false;
        }
    }
};