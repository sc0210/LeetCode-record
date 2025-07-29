/* 102. Binary Tree Level Order Traversal */

#include <queue>
#include <vector>
#include "treenode.h"

using std::queue;
using std::vector;

class Solution
{
public:
    vector<vector<int>> levelOrder(TreeNode *root)
    {
        vector<vector<int>> res;
        if (root == nullptr) {
            return res;
        }

        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty()) {
            int QSIZE = q.size();
            vector<int> level;
            for (int i = QSIZE; i > 0; i--) {
                TreeNode *node = q.front();
                q.pop();
                if (node != nullptr) {
                    level.push_back(node->val);
                    q.push(node->left);
                    q.push(node->right);
                }
            }
            if (!level.empty()) {
                res.push_back(level);
            }
        }
        return res;
    }
};