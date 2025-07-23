/* 39. Combination Sum */
#include <vector>
using std::vector;

class Solution
{
public:
    vector<vector<int>> res;
    vector<vector<int>> combinationSum(vector<int> &nums, int target)
    {
        vector<int> cur;
        backtrack(nums, target, 0, cur);
        return res;
    }

    void backtrack(const vector<int> &nums,
                   int target,
                   int index,
                   vector<int> &cur)
    {
        if (target == 0) {
            res.push_back(cur);
            return;
        }
        if (target < 0 || index >= nums.size()) {
            return;
        }

        cur.push_back(nums[index]);
        backtrack(nums, target - nums[index], index, cur);
        cur.pop_back();
        backtrack(nums, target, index + 1, cur);
    }
};