/* 28. Find the Index of the First Occurrence in a String */

#include <string>
using std::string;

class Solution
{
public:
    int strStr(string haystack, string needle)
    {
        // method1: string find API
        std::size_t found = haystack.find(needle);
        if (found == string::npos) {
            return -1;
        } else {
            return found;
        }

        // method2: fixed size window comparsion
        for (int i = 0; i <= haystack.length() - needle.length(); ++i) {
            if (haystack.substr(i, needle.length()) == needle) {
                return i;
            }
        }
        return -1;
    }
};