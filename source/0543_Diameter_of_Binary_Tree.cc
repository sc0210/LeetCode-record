/* 543. Diameter of Binary Tree */
/* 104 Maximum Deprth of BT extension */

#include <algorithm>
#include "treenode.h"

class Solution
{
public:
    int diameterOfBinaryTree(TreeNode *root)
    {
        int diameter = 0;
        dfs(root, diameter);
        return diameter;
    }

    // DFS
    int dfs(TreeNode *root, int &diameter)
    {
        if (root == nullptr)
            return 0;

        int leftMaxDepth = dfs(root->left, diameter);
        int rightMaxDepth = dfs(root->right, diameter);
        // update the max. diameter
        // opt.1 diameter: current max. diameter value
        // opt.2 bridge: set current ndoe as link to left and rigth
        diameter = std::max(diameter, leftMaxDepth + rightMaxDepth);
        // return the max. depth
        return 1 + std::max(leftMaxDepth, rightMaxDepth);
    }
};