/* 77. Combinations */

#include <vector>
using std::vector;

class Solution
{
public:
    vector<vector<int>> res;

    vector<vector<int>> combine(int n, int k)
    {
        vector<int> opt;
        backtrack(1, n, k, opt);
        return res;
    }

    void backtrack(int start, int n, int k, vector<int> &option)
    {
        if (option.size() == k) {
            res.push_back(option);
        }

        for (int i = start; i <= n; i++) {
            option.push_back(i);
            backtrack(i + 1, n, k, option);
            option.pop_back();
        }
    }
};