/* 235. Lowest Common Ancestor of a Binary Search Tree */
/* The target value(answer) should be include in [p,q],
   followed by BST property */

#include <algorithm>
#include "treenode.h"

class Solution
{
public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        // method1: recursive
        if (root == nullptr || p == nullptr || q == nullptr)
            return nullptr;

        if (std::min(p->val, q->val) > root->val) {
            return lowestCommonAncestor(root->right, p, q);
        } else if (std::max(p->val, q->val) < root->val) {
            return lowestCommonAncestor(root->left, p, q);
        } else {
            return root;
        }

        // method2: iterative
        // TreeNode *cur = root;
        // while (cur) {
        //     if (p->val > cur->val && q->val > cur->val) {
        //         cur = cur->right;
        //     } else if (p->val < cur->val && q->val < cur->val) {
        //         cur = cur->left;
        //     } else {
        //         return cur;
        //     }
        // }
        // return nullptr;
    }
};