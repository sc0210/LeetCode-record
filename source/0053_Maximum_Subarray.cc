/* 53. Maximum Subarray */
#include <vector>

class Solution
{
public:
    int maxSubArray(std::vector<int> &nums)
    {
        // Method1: Dynamic programing
        int maxSum = nums[0];      // 儲存全域最大值
        int currentSum = nums[0];  // 儲存以當前為結尾的最大子陣列和

        for (int i = 1; i < nums.size(); ++i) {
            currentSum = std::max(nums[i], currentSum + nums[i]);
            maxSum = std::max(maxSum, currentSum);
        }
        return maxSum;
    }

    // Method2: Divide and conquer
    // int helper(std::vector<int> &nums, int left, int right)
    // {
    //     if (left == right)
    //         return nums[left];

    //     int mid = (left + right) / 2;
    //     int leftMax = helper(nums, left, mid);
    //     int rightMax = helper(nums, mid + 1, right);

    //     // 中間跨越部分
    //     int leftSum = INT_MIN, sum = 0;
    //     for (int i = mid; i >= left; --i) {
    //         sum += nums[i];
    //         leftSum = std::max(leftSum, sum);
    //     }

    //     int rightSum = INT_MIN;
    //     sum = 0;
    //     for (int i = mid + 1; i <= right; ++i) {
    //         sum += nums[i];
    //         rightSum = std::max(rightSum, sum);
    //     }

    //     return std::max({leftMax, rightMax, leftSum + rightSum});
    // }

    // int maxSubArray(std::vector<int> &nums)
    // {
    //     return helper(nums, 0, nums.size() - 1);
    // }
};
