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
            // Mod all the numbers, val=0,1,...,(k-1)
            num %= k;

            // Traverse all the possible value after mod k
            for (int prev = 0; prev < k; ++prev) {
                /* The valid rule is that: (sub[0]+sub[1])==(sub[1]+sub[2])
                 *  dp[0][1] = dp[1][0] + 1 (add one for the appending
                 * substring) Ex:  0 ,1, 0,...
                 *
                 *  prev = 0: dp[0][1] = dp[1][0] + 1 = 0 + 1 = 1
                 *  prev = 1: dp[1][1] = dp[1][1] + 1 = 0 + 1 = 1
                 *  prev = 2: dp[2][1] = dp[1][2] + 1 = 0 + 1 = 1
                 */
                dp[prev][num] = dp[num][prev] + 1;
                // update the maximum value
                res = std::max(res, dp[prev][num]);
            }
        }
        return res;
    }
};