/* 91. Decode Ways */

#include <string>
#include <unordered_map>
#include <vector>

using std::string;
using std::unordered_map;
using std::vector;

// method1: recursion (TLE)

// class Solution {
// public:
//     int numDecodings(string s) {
//         return dfs(0, s);
//     }
// private:
//     int dfs(int i, string& s){
//         if(i == s.size()) return 1;
//         if(s[i] == '0') return 0;

//         // case: one digit (1~9)
//         int res = dfs(i+1, s);
//         // case: two digit (10~19, 20~26)
//         if(i < s.size()-1){
//             if(s[i]=='1' || (s[i]=='2' && s[i+1]<'7')){
//                 res += dfs(i+2, s);
//             }
//         }
//         return res;
//     }
// };

// method2: dp(Top-Down)

// class Solution
// {
// public:
//     int numDecodings(string s)
//     {
//         unordered_map<int, int> dp;
//         dp[s.size()] = 1;
//         return dfs(s, 0, dp);
//     }

// private:
//     int dfs(string s, int i, unordered_map<int, int> &dp)
//     {
//         if (dp.count(i))
//             return dp[i];
//         if (s[i] == '0')
//             return 0;

//         // case1: one digit (1~9)
//         int res = dfs(s, i + 1, dp);
//         // case2: two digit (10~19, 20~26)
//         if (i + 1 < s.size() &&
//             (s[i] == '1' || s[i] == '2' && s[i + 1] < '7')) {
//             res += dfs(s, i + 2, dp);
//         }
//         // memorization
//         dp[i] = res;
//         return res;
//     }
// };

// method3: dp(Bottom-up)

class Solution
{
public:
    int numDecodings(string s)
    {
        vector<int> dp(s.size() + 1);
        dp[s.size()] = 1;
        for (int i = s.size() - 1; i >= 0; i--) {
            if (s[i] == '0') {
                dp[i] = 0;
            } else {
                // case1: one digit (1~9)
                dp[i] = dp[i + 1];
                // case2: two digit (10~19, 20~26)
                if (i + 1 < s.size() &&
                    (s[i] == '1' || s[i] == '2' && s[i + 1] < '7')) {
                    dp[i] += dp[i + 2];
                }
            }
        }
        return dp[0];
    }
};
