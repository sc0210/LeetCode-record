/* 104. Maximum Depth of Binary Tree */

#include <queue>
#include "treenode.h"

class Solution
{
public:
    int maxDepth(TreeNode *root)
    {
        // DFS (recursive)
        // if (root == nullptr) {
        //     return 0;
        // }
        // int leftDepth = maxDepth(root->left);
        // int rightDepth = maxDepth(root->right);
        // return 1 + std::max(leftDepth, rightDepth);

        // BFS (queue)
        int maxDepth = 0;
        if (root == nullptr) {
            return maxDepth;
        }
        std::queue<TreeNode *> q;
        q.push(root);

        while (!q.empty()) {
            int Q_SIZE = q.size();
            for (int i = Q_SIZE; i > 0; i--) {
                TreeNode *node = q.front();
                q.pop();
                if (node->left) {
                    q.push(node->left);
                }
                if (node->right) {
                    q.push(node->right);
                }
            }
            maxDepth++;
        }
        return maxDepth;
    }
};