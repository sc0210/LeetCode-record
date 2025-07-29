/* 572 Subtree of Another Tree */
/* 100 same tree */

#include "treenode.h"

class Solution
{
public:
    bool isSubtree(TreeNode *root, TreeNode *subRoot)
    {
        if (subRoot == nullptr) {
            return true;  // without subRoot
        }
        if (root == nullptr) {
            return false;  // with subRoot, without root
        }
        if (sameTree(root, subRoot)) {
            return true;
        }
        // recursive find wether subtree match
        return isSubtree(root->left, subRoot) ||
               isSubtree(root->right, subRoot);
    }

    bool sameTree(TreeNode *root, TreeNode *subRoot)
    {
        // When both are is nullptr, return true
        if (root == nullptr && subRoot == nullptr) {
            return true;
        }
        // when both are not nullptr, compare the value
        // recursive check left and right subtree
        if (root != nullptr && subRoot != nullptr &&
            root->val == subRoot->val) {
            return sameTree(root->left, subRoot->left) &&
                   sameTree(root->right, subRoot->right);
        }
        return false;
    }
};
