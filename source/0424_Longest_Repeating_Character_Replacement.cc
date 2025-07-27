/* 424. Longest Repeating Character Replacement */

#include <string>
#include <unordered_map>

class Solution
{
public:
    int characterReplacement(std::string s, int k)
    {
        std::unordered_map<char, int> count;
        int l = 0, maxlen = 0, maxf = 0;

        for (int r = 0; r < s.size(); r++) {
            count[s[r]]++;
            maxf = std::max(maxf, count[s[r]]);

            // Invalid, don't have chances to change the letters
            while ((r - l + 1) - maxf > k) {
                count[s[l]]--;
                l++;
            }
            // Update maxlen
            maxlen = std::max(maxlen, r - l + 1);
        }
        return maxlen;
    }
};
