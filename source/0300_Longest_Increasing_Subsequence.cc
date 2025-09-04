/* 300. Longest Increasing Subsequence */

#include <vector>
using std::vector;

class Solution
{
public:
    int lengthOfLIS(vector<int> &nums)
    {
        int n = nums.size();
        memo.assign(n, -1);  // dp array

        int maxLIS = 1;
        for (int i = 0; i < n; i++) {
            maxLIS = std::max(maxLIS, dfs(nums, i));
        }
        return maxLIS;
    }

private:
    vector<int> memo;
    int dfs(vector<int> &nums, int i)
    {
        // return the value stored in dp array
        if (memo[i] != -1)
            return memo[i];

        // calculate LIS, add the LIS when is valid
        // ( next number larger than previous)
        int LIS = 1;
        for (int j = i + 1; j < nums.size(); j++) {
            if (nums[i] < nums[j])
                LIS = std::max(LIS, 1 + dfs(nums, j));
        }
        // store and return the value in dp array
        return memo[i] = LIS;
    }
};
