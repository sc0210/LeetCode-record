/* 199. Binary Tree Right Side View */

#include <queue>
#include <vector>
#include "treenode.h"
using std::queue;
using std::vector;

class Solution
{
public:
    vector<int> rightSideView(TreeNode *root)
    {
        // BFS
        vector<int> res;
        if (root == nullptr) {
            return res;
        }

        queue<TreeNode *> q;
        q.push(root);

        while (!q.empty()) {
            vector<int> level;
            int QSIZE = q.size();

            for (int i = QSIZE; i > 0; i--) {
                TreeNode *node = q.front();
                q.pop();
                if (node != nullptr) {
                    q.push(node->left);
                    q.push(node->right);
                    level.push_back(node->val);
                }
            }
            if (!level.empty()) {
                res.push_back(level.back());
            }
        }
        return res;
    }
};