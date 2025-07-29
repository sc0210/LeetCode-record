/* 226. Invert Binary Tree */

#include <queue>
#include "treenode.h"

class Solution
{
public:
    TreeNode *invertTree(TreeNode *root)
    {
        // method1: DFS (recursive)
        // if (root == nullptr) {
        //     return root;
        // }
        // std::swap(root->left, root->right);
        // invertTree(root->left);
        // invertTree(root->right);
        // return root;

        // method2: BFS (queue)
        if (root == nullptr) {
            return root;
        }
        std::queue<TreeNode *> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode *node = q.front();
            q.pop();
            std::swap(node->left, node->right);
            if (node->left)
                q.push(node->left);
            if (node->right)
                q.push(node->right);
        }
        return root;
    }
};
