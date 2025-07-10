/* 283. Move Zeros */
#include <vector>

class Solution
{
public:
    void moveZeroes(std::vector<int> &nums)
    {
        int l = 0, r = 0;

        while (r < nums.size()) {
            // When the value is not 0, then insert in the right place
            if (nums[r] != 0) {
                nums[l] = nums[r];
                l++;
            }
            // Move to next pointer
            r++;
        }

        // when all valid value is insert, the reset index is set to 0
        while (l < nums.size()) {
            nums[l++] = 0;
        }
    }
};