/* 268. Missing Number */

#include <numeric>
#include <vector>


class Solution
{
public:
    int missingNumber(std::vector<int> &nums)
    {
        int N = nums.size();
        std::vector<int> r(N + 1);
        std::iota(r.begin(), r.end(), 0);  // Fill with 0, 2, ..., 10

        int current_sum = std::accumulate(nums.begin(), nums.end(), 0);
        int original_sum = std::accumulate(r.begin(), r.end(), 0);
        // original_sum = (1 + N) * N / 2;
        return original_sum - current_sum;
    }
};