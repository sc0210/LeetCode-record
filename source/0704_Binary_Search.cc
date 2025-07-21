/* 704. Binary Search */

#include <vector>

class Solution
{
public:
    int search(std::vector<int> &nums, int target)
    {
        int l = 0, r = nums.size() - 1;
        while (l <= r) {
            int m = (l + r) / 2;
            // when match with target
            if (nums[m] == target) {
                return m;
            } else if (nums[m] > target) {
                r = m - 1;

            } else {
                l = m + 1;
            }
        }

        // when not match, don't existed
        return -1;
    }
};