/* 230. Kth Smallest Element in a BST */
#include <vector>
#include "treenode.h"

class Solution
{
public:
    int kthSmallest(TreeNode *root, int k)
    {
        // method1: Inorder Traversal
        // std::vector<int> res;
        // dfs(res, root);
        // return res[k - 1];

        // method2: Morris Traversal
        TreeNode *curr = root;

        while (curr != nullptr) {
            if (!curr->left) {
                k--;
                // get the k-th smallest value
                if (k == 0)
                    return curr->val;
                curr = curr->right;
            } else {
                TreeNode *pred = curr->left;
                while (pred->right && pred->right != curr)
                    pred = pred->right;

                if (!pred->right) {
                    pred->right = curr;
                    curr = curr->left;
                } else {
                    pred->right = nullptr;
                    k--;
                    if (k == 0)
                        return curr->val;
                    curr = curr->right;
                }
            }
        }
        return -1;
    }

    void dfs(std::vector<int> &res, TreeNode *root)
    {
        if (root == nullptr)
            return;

        // Inorder traversal (L,D,R)
        if (root->left)
            dfs(res, root->left);
        res.push_back(root->val);
        if (root->right)
            dfs(res, root->right);
    }
};