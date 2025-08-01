/* 1448. Count Good Nodes in Binary Tree */
#include <algorithm>
#include <queue>
#include "treenode.h"

class Solution
{
public:
    int goodNodes(TreeNode *root)
    {
        if (root == nullptr) {
            return 0;
        }

        int res = 0;
        // matian a maxVal of the root to current node
        std::queue<std::pair<TreeNode *, int>> q;
        q.push({root, -INT_MAX});

        while (!q.empty()) {
            auto tmp = q.front();
            TreeNode *node = tmp.first;
            int CurrMax = tmp.second;

            q.pop();
            // if node is not nullptr
            if (node) {
                // valid case, current value is greater than the maxVal
                if (node->val >= CurrMax) {
                    res++;
                }
                // iterate to left subtree if existed
                if (node->left) {
                    q.push({node->left, std::max(node->val, CurrMax)});
                }
                // iterate to right subtree if existed
                if (node->right) {
                    q.push({node->right, std::max(node->val, CurrMax)});
                }
            }
        }
        return res;
    }
};