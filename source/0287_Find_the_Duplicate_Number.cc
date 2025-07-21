/* 287. Find the Duplicate Number */
#include <unordered_set>
#include <vector>

class Solution
{
public:
    int findDuplicate(std::vector<int> &nums)
    {
        std::unordered_set<int> seen;
        for (auto val : nums) {
            if (seen.count(val))
                return val;
            seen.insert(val);
        }
    }
};
