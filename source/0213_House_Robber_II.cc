/* 213. House Robber II */

#include <vector>

class Solution
{
public:
    int rob(std::vector<int> &nums)
    {
        /*
            seperate into two cases, (circular array)
            - num1: involve first, but not involve the last element
            - num2: not involve first, but involve the last element
         */
        std::vector<int> num1(nums.begin(), nums.end() - 1);
        std::vector<int> num2(nums.begin() + 1, nums.end());
        return std::max(nums[0], std::max(dfs(num1), dfs(num2)));
    }

    int dfs(std::vector<int> &nums)
    {
        if (nums.empty()) {
            return 0;
        }
        if (nums.size() == 1) {
            return nums[0];
        }
        // rob1, rob2, num, num+1, ..
        int rob1 = 0, rob2 = 0, temp;
        for (int num : nums) {
            temp = std::max(rob1 + num, rob2);
            rob1 = rob2;
            rob2 = temp;
        }
        return temp;
    }
};