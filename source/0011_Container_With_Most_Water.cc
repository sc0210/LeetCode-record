/* 11 Container With Most Water */
#include <vector>

class Solution
{
public:
    int maxArea(std::vector<int> &height)
    {
        // Method: two pointers
        int l = 0, r = height.size() - 1;

        int width = (r - l);
        int area = std::min(height[l], height[r]) * width;
        int maxArea = area;
        // When only existed two elemenets, return
        if (height.size() == 2)
            return maxArea;

        while (l < r) {
            // Move the pointer that points to the lower line
            (height[l] < height[r]) ? l++ : r--;

            area = std::min(height[l], height[r]) * (r - l);
            maxArea = std::max(maxArea, area);
        }
        return maxArea;
    }
};