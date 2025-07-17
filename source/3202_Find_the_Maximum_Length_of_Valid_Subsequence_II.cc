/* 3202. Find the Maximum Length of Valid Subsequence II */

#include <vector>
using std::vector;

class Solution
{
public:
    int maximumLength(vector<int> &nums, int k)
    {
        vector<vector<int>> dp(k, vector<int>(k, 0));
        int res = 0;
        for (int num : nums) {
            num %= k;
            printf("%d ", num);
            for (int prev = 0; prev < k; ++prev) {
                dp[prev][num] = dp[num][prev] + 1;
                res = std::max(res, dp[prev][num]);
            }
        }
        return res;
    }
};