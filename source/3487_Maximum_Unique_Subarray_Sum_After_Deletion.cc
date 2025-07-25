/* 3487. Maximum Unique Subarray Sum After Deletion */
#include <unordered_set>
#include <vector>

using std::unordered_set;
using std::vector;

class Solution
{
public:
    int maxSum(vector<int> &nums)
    {
        // Method1, O(N)
        int maxSum = 0;
        unordered_set<int> seen;

        for (int idx = 0; idx < nums.size(); idx++) {
            int val = nums[idx];
            // ignore negative
            if (val <= 0)
                continue;
            // ignore duplicate
            else if (seen.find(val) != seen.end())
                continue;
            // add the new value
            else if (seen.find(val) == seen.end()) {
                seen.insert(val);
                maxSum += val;
            }
        }

        // All value are negative (cause empty after deletion)
        if (maxSum == 0) {
            /*
             *  reset the maxSum to the first element
             *  when only one element in the nums
             */
            maxSum = nums[0];
            // compare through all the negative and pick the larger one
            maxSum = *max_element(nums.begin(), nums.end());
        }

        // Method2, O(NlogN) sorting
        // sort(nums.begin(), nums.end(), greater<int> ());

        // /*  handle when all the integer in nums is negative,
        //     retrun the largest element in nums (nums[0])
        // */
        // if(nums[0]<0) return nums[0];
        // unordered_map<int,int> hp;
        // for(int val : nums){
        //     hp[val]++;
        // }

        // int maxSum = 0;
        // for(const auto &pair : hp){
        //     // sum all the positive integer
        //     if(pair.first>=0) maxSum+=pair.first;
        // }

        return maxSum;
    }
};