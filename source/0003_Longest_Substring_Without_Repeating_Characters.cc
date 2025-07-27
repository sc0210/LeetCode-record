/* 3. Longest Substring Without Repeating Characters */

#include <string>
#include <unordered_set>

class Solution
{
public:
    int lengthOfLongestSubstring(std::string s)
    {
        int l = 0, res = 0;
        std::unordered_set<char> seen;

        for (int r = 0; r < s.length(); r++) {
            // when dupliacte, shift the left pointer update hashset
            while (seen.find(s[r]) != seen.end()) {
                seen.erase(s[l]);
                l++;
            }
            // insert the char into hashset
            seen.insert(s[r]);
            res = std::max(res, r - l + 1);
        }
        return res;
    }
};