/* 1717. Maximum Score From Removing Substrings */
#include <string>
using std::string;

class Solution
{
public:
    int maximumGain(string s, int x, int y)
    {
        // x: "ab", y: "ba"

        if (x < y) {
            // always set the high value to x
            std::swap(x, y);              // swap the score
            reverse(s.begin(), s.end());  // swap the string
        }

        // Now x >= y, and we remove all "ab" first, then "ba"
        int total = 0;
        string temp;
        for (char c : s) {
            if (!temp.empty() && temp.back() == 'a' && c == 'b') {
                temp.pop_back();
                total += x;
            } else {
                temp.push_back(c);
            }
        }

        // Now remove "ba" from remaining stack
        string finalTemp;
        for (char c : temp) {
            if (!finalTemp.empty() && finalTemp.back() == 'b' && c == 'a') {
                finalTemp.pop_back();
                total += y;
            } else {
                finalTemp.push_back(c);
            }
        }

        return total;
    }
};
