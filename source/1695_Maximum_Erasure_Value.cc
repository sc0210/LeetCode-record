/* 1695. Maximum Erasure Value */

#include <unordered_set>
#include <vector>

class Solution
{
public:
    int maximumUniqueSubarray(std::vector<int> &nums)
    {
        std::unordered_set<int> seen;
        int l = 0, windowSum = 0, maxSum = 0;

        for (int r = 0; r < nums.size(); r++) {
            while (seen.find(nums[r]) != seen.end()) {
                seen.erase(nums[l]);
                windowSum -= nums[l];
                l++;
            }
            seen.insert(nums[r]);
            windowSum += nums[r];
            maxSum = std::max(maxSum, windowSum);
        }

        return maxSum;
    }
};

// class Solution {
// public:
//     int maximumUniqueSubarray(std::vector<int>& nums) {
//         unordered_set<int> seen;
//         int l = 0, r = 0;
//         int sum = 0, maxSum = 0;

//         while (r < nums.size()) {
//             if (seen.find(nums[r]) == seen.end()) {
//                 // 沒出現過，加入集合與當前總和
//                 seen.insert(nums[r]);
//                 sum += nums[r];
//                 maxSum = max(maxSum, sum);
//                 r++;
//             } else {
//                 // 出現過，移除最左邊的直到不重複
//                 seen.erase(nums[l]);
//                 sum -= nums[l];
//                 l++;
//             }
//         }

//         return maxSum;
//     }
// };
