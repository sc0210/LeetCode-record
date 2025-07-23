/* 78. Subsets */
#include <vector>
using std::vector;

class Solution
{
public:
    vector<vector<int>> res;

    vector<vector<int>> subsets(vector<int> &nums)
    {
        vector<int> path;
        backtrack(nums, 0, path);
        return res;
    }

    void backtrack(vector<int> &nums, int start, vector<int> &path)
    {
        // add to res (one possible subsets)
        res.push_back(path);
        for (int i = start; i < nums.size(); ++i) {
            // add current number
            path.push_back(nums[i]);
            // backtrack
            backtrack(nums, i + 1, path);
            // remove current number
            path.pop_back();
        }
    }
};