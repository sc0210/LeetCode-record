
#include <iostream>
#include "treenode.h"


int dfs(TreeNode *node, int &res)
{
    if (node == nullptr)
        return 0;

    int leftMax = std::max(dfs(node->left, res), 0);
    int rightMax = std::max(dfs(node->right, res), 0);

    // update the maximum path sum encountered so far (with split)
    res = std::max(res, node->val + leftMax + rightMax);

    // Return the maximum sum of the path (without spit)
    return node->val + std::max(leftMax, rightMax);
}

int maxPathSum(TreeNode *root)
{
    int res = INT_MIN;
    dfs(root, res);
    return res;
}


int main(void)
{
    return 0;
}