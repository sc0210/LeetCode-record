/* 110. Balanced Binary Tree */

#include <algorithm>
#include "treenode.h"

class Solution
{
public:
    bool isBalanced(TreeNode *root)
    {
        // method1: brute force, O(N^2)
        // // when root is null, isbalanced
        // // if (root == nullptr) {
        // //     return true;
        // // }
        // // DFS, when leftDepth-rightDepth>1, return false
        // int leftDepth = getDepth(root->left);
        // int rightDepth = getDepth(root->right);
        // // when leftDepth-rightDepth>1, return false
        // if (abs(leftDepth - rightDepth) > 1) {
        //     return false;
        // }
        // // recursive check the remainder part
        // return (isBalanced(root->left) && isBalanced(root->right));

        // method2: DFS (recursive)
        // return vector:
        //      first bit represent balanced (1:balanced, 0:imbalanced)
        //      second bit represent height (maxDepth from root)
        return dfs(root).first == 1;
    }

    int getDepth(TreeNode *root)
    {
        if (root == nullptr) {
            return 0;
        }
        int leftDepth = getDepth(root->left);
        int rigthDepth = getDepth(root->right);
        return 1 + (std::max(leftDepth, rigthDepth));
    }

    std::pair<int, int> dfs(TreeNode *root)
    {
        if (root == nullptr) {
            return {1, 0};
        }

        std::pair<int, int> left = dfs(root->left);
        std::pair<int, int> right = dfs(root->right);

        // update wether balanced or not
        bool balanced = (left.first == 1 && right.first == 1) &&
                        (abs(left.second - right.second) <= 1);

        // Update the Depth from root
        int height = 1 + std::max(left.second, right.second);

        return {balanced ? 1 : 0, height};
    }
};