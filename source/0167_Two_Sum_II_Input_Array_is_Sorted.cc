/* 167 Two Sum II - Input Array Is Sorted */
#include <vector>

class Solution
{
public:
    std::vector<int> twoSum(std::vector<int> &numbers, int target)
    {
        int l = 0, r = numbers.size() - 1;

        while (l < r) {
            int rem = target - numbers[l] - numbers[r];
            if (rem == 0)
                break;
            else if (rem < 0)
                r--;
            else
                l++;
        }

        return {l + 1, r + 1};
    }
};