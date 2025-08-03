/* 242. Valid Anagram */

#include <string>
#include <vector>
using std::string;
using std::vector;

class Solution
{
public:
    bool isAnagram(string s, string t)
    {
        // when two string length is not equal, invalid
        if (s.size() != t.size())
            return false;

        // use vector to store the frequency of 26 alphabet
        vector<int> smap(26, 0);
        vector<int> tmap(26, 0);

        for (const char ch : s)
            smap[ch - 'a']++;
        for (const char ch : t)
            tmap[ch - 'a']++;

        // compare wether two vector is the same
        return smap == tmap;
    }
};