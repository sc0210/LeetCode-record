/* 567. Permutation in String */

#include <string>
#include <vector>

class Solution
{
public:
    bool checkInclusion(std::string s1, std::string s2)
    {
        // when the source(s2) is larger than target(s1), invalid
        if (s1.length() > s2.length())
            return false;

        // calculate char and its count
        std::vector<int> s1Count(26, 0);
        std::vector<int> s2Count(26, 0);

        // base(s1.length), update s1Count and s2COunt
        for (int i = 0; i < s1.length(); i++) {
            s1Count[s1[i] - 'a']++;
            s2Count[s2[i] - 'a']++;
        }

        // base(s1.length), update matches
        int matches = 0;
        for (int i = 0; i < 26; i++) {
            if (s1Count[i] == s2Count[i])
                matches++;
        }

        // others(s1.length -> s2.length)
        for (int l = 0, r = s1.length(); r < s2.length(); l++, r++) {
            if (matches == 26) {
                return true;
            }

            // the right hand window char (append)
            int index = s2[r] - 'a';
            s2Count[index]++;
            if (s1Count[index] == s2Count[index]) {
                matches++;
            } else if (s1Count[index] + 1 == s2Count[index]) {
                matches--;
            }

            // the left hand window char (delete)
            index = s2[l] - 'a';
            s2Count[index]--;
            if (s1Count[index] == s2Count[index]) {
                matches++;
            } else if (s1Count[index] - 1 == s2Count[index]) {
                matches--;
            }
        }
        return matches == 26;
    }
};
