/* 647. Palindromic Substrings */

#include <string>
using std::string;

class Solution
{
public:
    int countSubstrings(string s)
    {
        int res = 0;
        for (int i = 0; i < s.size(); i++) {
            res += countPali(s, i, i);      // odd-length palindrome
            res += countPali(s, i, i + 1);  // even-length palindrome
        }
        return res;
    }

private:
    int countPali(string s, int l, int r)
    {
        int res = 0;
        while (l >= 0 && r < s.size() && s[l] == s[r]) {
            res++;
            l--;
            r++;
        }
        return res;
    }
};