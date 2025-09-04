/* 215. Kth Largest Element in an Array */

#include <queue>
#include <vector>

class Solution
{
public:
    int findKthLargest(std::vector<int> &nums, int k)
    {
        std::priority_queue<int> pq(nums.begin(), nums.end());
        k--;
        while (k--) {
            pq.pop();
        }
        return pq.top();
    }
};
