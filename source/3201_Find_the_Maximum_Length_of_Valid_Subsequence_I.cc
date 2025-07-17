#include<vector>

class Solution {
public:
    int maximumLength(std::vector<int>& nums) {
        int res = 0;
        std::vector<std::vector<int>> patterns = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
        // 4 cases match to the patterns
        for (auto& pattern : patterns) {
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