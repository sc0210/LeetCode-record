/* 198. House Robber */
#include <vector>

class Solution
{
public:
    int rob(std::vector<int> &nums)
    {
        // Bottom up, space O(N)
        // if(nums.empty()) return 0;
        // if(nums.size()==1) return nums[0];

        // vector<int> dp(nums.size());
        // dp[0] = nums[0];
        // dp[1] = max(nums[0], nums[1]);

        // for(int i=2; i<nums.size(); i++){
        //     dp[i] = max(dp[i-1], nums[i]+dp[i-2]);
        // }
        // return dp[nums.size()-1];

        // Space optimized: O(1)
        // [rob1, rob2, n, n+1, n+2,...]
        int rob1 = 0, rob2 = 0;

        for (int num : nums) {
            int temp = std::max(num + rob1, rob2);
            rob1 = rob2;  //
            rob2 = temp;  // current max
        }
        return rob2;
    }
};