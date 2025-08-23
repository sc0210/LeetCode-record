/* 190. Reverse Bits */

class Solution
{
public:
    int reverseBits(int n)
    {
        int res = 0;
        for (int i = 0; i < 32; i++) {
            if (n & 1 << (31 - i)) {
                res |= (1 << i);  // set bit to one;
            }
        }
        return res;
    }
};