/* 98. Validate Binary Search Tree */

#include <queue>
#include "climits"
#include "treenode.h"

class Solution
{
public:
    bool isValidBST(TreeNode *root)
    {
        if (root == nullptr) {
            return true;
        }
        // keep minVal of left side and maxVal of right size
        // pair<T,T>, tuple<T,T,T>
        std::queue<std::tuple<TreeNode *, long, long>> q;
        q.push(std::make_tuple(root, LONG_MIN, LONG_MAX));

        while (!q.empty()) {
            auto [node, MinLeft, MaxRight] = q.front();
            q.pop();

            // when node is not nullptr
            if (node) {
                // invalid case for BST, return false, END
                if (!(MinLeft < node->val && node->val < MaxRight)) {
                    return false;
                }
                // iterate to left subtree to check validness of BST
                // update the MaxRight to current val (node->val), BST property
                if (node->left) {
                    q.push(std::make_tuple(node->left, MinLeft, node->val));
                }
                // iterate to right subtree to check validness of BST
                // update the MinLeft to current val (node->val), BST property
                if (node->right) {
                    q.push(std::make_tuple(node->right, node->val, MaxRight));
                }
            }
        }
        return true;
    }
};