/* 16. 3Sum Closest */
#include <vector>

class Solution
{
public:
    int threeSumClosest(std::vector<int> &nums, int target)
    {
        sort(nums.begin(), nums.end());

        int N = nums.size();
        int ans = 10e5;

        for (int l = 0; l < N - 2; l++) {
            int p1 = l + 1;
            int p2 = N - 1;
            while (p1 < p2) {
                // calculate the current sum of three number
                int sum = nums[l] + nums[p1] + nums[p2];
                // update the closeest sum to the target
                ans = (abs(target - sum) < abs(target - ans)) ? sum : ans;

                // shift p1 or p2 pointer based on margin between target and sum
                if ((target - sum) > 0)
                    p1++;
                else if ((target - sum) < 0)
                    p2--;
                else if (target == sum)
                    return target;
            }
        }
        return ans;
    }
};