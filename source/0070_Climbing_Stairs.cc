/* 70. Climbing Stairs */
// #include <vector>
// using std::vector;

class Solution
{
public:
    int climbStairs(int n)
    {
        // edge case, initial state
        if (n == 0 || n == 1)
            return 1;

        // when n = 3,4,5,...

        // method2: memorization
        // vector<int> res(n+1, 0);
        // res[0] = 0, res[1] = 1, res[2] = 2;
        // for(int i=2; i<=n; i++){
        //     res[i] = res[i-1] + res[i-2];
        // }
        // return res[n];

        // method2: space optimized
        int prev = 1, cur = 1;
        for (int i = 2; i <= n; i++) {
            int temp = cur;
            cur = prev + cur;
            prev = temp;
        }
        return cur;
    }
};