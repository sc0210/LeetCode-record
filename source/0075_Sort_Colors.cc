/* 75 Sort Colors */
#include <vector>

class Solution
{
public:
    void sortColors(std::vector<int> &nums)
    {
        // Method1: two pointer
        int l = 0, r = 0;
        // iterate through 3 colos(k=0,1,2)
        for (int k = 0; k < 3; k++) {
            r = l;
            while (r < nums.size()) {
                // when find a match, then swap to correct palce
                if (nums[r] == k) {
                    // l pointer keeps the index
                    std::swap(nums[l], nums[r]);
                    l++;
                }
                r++;
            }
        }

        // Method2: Dutch National Flag Algorithm
        /* Source:
            https://leetcode.com/problems/sort-colors/solutions/6751648/dutch-national-flag-algorithm-with-images-example-walkthrough-c-python-java/
        */
        int low = 0, mid = 0;
        int high = nums.size() - 1;

        while (mid <= high) {
            if (nums[mid] == 0) {
                std::swap(nums[mid++], nums[low++]);
            } else if (nums[mid] == 1) {
                mid++;
            } else {
                std::swap(nums[mid], nums[high--]);
            }
        }
    }
};