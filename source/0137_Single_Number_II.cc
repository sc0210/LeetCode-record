/* 137. Single Number II */

#include <unordered_map>
#include <vector>

class Solution
{
public:
    int singleNumber(std::vector<int> &nums)
    {
        std::unordered_map<int, int> hm;
        for (const auto &val : nums) {
            if (hm.find(val) == hm.end())
                hm[val] = 1;
            else
                hm[val]++;
        }

        for (const auto &item : hm) {
            if (item.second == 1)
                return item.first;
        }
        return -1;
    }
};