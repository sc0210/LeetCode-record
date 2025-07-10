/* 26 Remove Duplicates from sorted array */
#include <vector>

class Solution
{
public:
    int removeDuplicates(std::vector<int> &nums)
    {
        int l = 0, r = 0;
        int cnt = 1;

        while (r < nums.size()) {
            // When next index is not duplicate(cnt++), store the value(l++)
            if (nums[r] != nums[l]) {
                l++;
                cnt++;
            }
            // Update the nums vector,
            // When duplicate, nums[r] = nums[r+1] = ...
            // When unique, it will sotre in the right places
            nums[l] = nums[r];

            // iterate to next index
            r++;
        }

        return cnt;
    }
};