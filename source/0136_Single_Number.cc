/* 136. Single Number */

#include <vector>

class Solution
{
public:
    int singleNumber(std::vector<int> &nums)
    {
        int res = 0;
        for (auto val : nums) {
            res ^= val;  // XOR, bitwise p[]
            /*  XOR true table
                x    y   x XOR y
                0    0      0
                0    1      1
                1    0      1
                1    1      0

                0 ^ x => x
                1 ^ x => x'
                x ^ x => 0
            */
        }
        return res;
    }
};