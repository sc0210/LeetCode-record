/* 3201 Find the Maximum Length of Valid Subsequence I */

#include <vector>
using std::vector;

class Solution
{
public:
    int maximumLength(vector<int> &nums)
    {
        int res = 0;
        vector<vector<int>> patterns = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
        // 4 cases match to the patterns
        for (auto &pattern : patterns) {
            int cnt = 0;
            // traverse the vector to find count for each cases
            for (int num : nums) {
                if (num % 2 == pattern[cnt % 2]) {
                    cnt++;
                }
            }
            // update the maximun number
            res = std::max(res, cnt);
        }
        return res;
    }
};