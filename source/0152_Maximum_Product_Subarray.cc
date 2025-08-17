/* 152. Maximum Product Subarray */
/*
    Topic: 1-D dynamic programming
    Solutions:
    - Kadane's Algorithm: Time:O(N), Space:O(1)
    - Brute force: Time:O(N^2), Space:O(1)
*/

#include <vector>

class Solution
{
public:
    int maxProduct(std::vector<int> &nums)
    {
        int res = nums[0];
        int curMin = 1, curMax = 1;

        for (const int &num : nums) {
            // To avoid changing the curMax value in the next line
            int tmp = curMax * num;
            curMax = std::max(std::max(tmp, curMin * num), num);
            curMin = std::min(std::min(tmp, curMin * num), num);
            // update the maximum subarray product so fars
            res = std::max(curMax, res);
        }
        return res;
    }
};