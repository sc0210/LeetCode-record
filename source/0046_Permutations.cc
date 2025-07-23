/* 46. Permutations */

#include <vector>
using std::vector;

class Solution
{
public:
    vector<vector<int>> res;

    vector<vector<int>> permute(vector<int> &nums)
    {
        vector<bool> used(nums.size(), false);
        vector<int> path;

        backtrack(nums, used, path);
        return res;
    }

    void backtrack(vector<int> &nums, vector<bool> &used, vector<int> &path)
    {
        // when met to the end of backtracking
        if (path.size() == nums.size()) {
            res.push_back(path);
            return;
        }
        // backtracking
        for (int i = 0; i < nums.size(); ++i) {
            // if used, then passed
            if (used[i])
                continue;
            // if not used, mark as used
            used[i] = true;
            path.push_back(nums[i]);
            backtrack(nums, used, path);

            path.pop_back();
            used[i] = false;
        }
    }
};