/* 90. Subsets II */

#include <set>
#include <vector>

using std::set;
using std::vector;

class Solution
{
    set<vector<int>> res;

public:
    vector<vector<int>> subsetsWithDup(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        backtrack(nums, 0, {});
        return vector<vector<int>>(res.begin(), res.end());
    }

    void backtrack(vector<int> &nums, int i, vector<int> subset)
    {
        // Termination, when the size of subset is match
        if (i == nums.size()) {
            res.insert(subset);
            return;
        }

        // Recursive
        // 1- All subset that include nums[i]
        subset.push_back(nums[i]);
        backtrack(nums, i + 1, subset);

        // 2- All subset that not include nums[i]
        subset.pop_back();
        // skip the duplicate number
        while (i + 1 < nums.size() && nums[i] == nums[i + 1]) {
            i++;
        }
        backtrack(nums, i + 1, subset);
    }
};