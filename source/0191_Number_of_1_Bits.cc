/* 191. Number of 1 Bits */

class Solution
{
public:
    int hammingWeight(int n)
    {
        // Method1: Bitmask-1
        // int res = 0;
        // for(int i=0; i<32; i++){
        //   if( (1<<i)&n) res++;
        // }
        // return res;

        // Method2: Bitmast-2
        int res = 0;
        for (int i = 0; i < 32; i++) {
            if (n & 1)
                res++;
            n = n >> 1;
        }
        return res;

        // Method3: Built-in function
        return __builtin_popcount(n);
    }
};