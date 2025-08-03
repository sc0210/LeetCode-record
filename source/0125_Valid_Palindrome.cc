/* 125. Valid Palindrome */

#include <string>
using std::string;

class Solution
{
public:
    bool isPalindrome(string s)
    {
        string convert = "";
        for (const char ch : s) {
            // alphabetic
            if (isalpha(ch))
                convert += tolower(ch);
            // digits
            else if (isdigit(ch))
                convert += ch;
        }

        for (int Index = 0; Index < convert.size() / 2; Index++) {
            if (convert[Index] != convert[convert.size() - Index - 1])
                return false;
        }
        return true;
    }
};