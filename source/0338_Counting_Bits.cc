/* 338. Counting Bits */

#include <vector>

class Solution
{
public:
    std::vector<int> countBits(int n)
    {
        std::vector<int> res(n + 1, 0);

        for (int i = 0; i < n + 1; i++) {
            // Counting the bits for all the integer i=0~n
            for (int j = 0; j < 32; j++) {
                if (i & (1 << j))
                    res[i]++;
            }
        }
        return res;
    }
};