/* 17. Letter Combinations of a Phone Number */
#include <string>
#include <unordered_map>
#include <vector>


using std::string;
using std::vector;

class Solution
{
public:
    vector<string> res;
    std::unordered_map<int, vector<char>> dict = {
        {2, {'a', 'b', 'c'}}, {3, {'d', 'e', 'f'}},
        {4, {'g', 'h', 'i'}}, {5, {'j', 'k', 'l'}},
        {6, {'m', 'n', 'o'}}, {7, {'p', 'q', 'r', 's'}},
        {8, {'t', 'u', 'v'}}, {9, {'w', 'x', 'y', 'z'}}};

    vector<string> letterCombinations(string digits)
    {
        if (digits.empty())
            return res;

        string opt;
        backtrack(0, digits, opt);
        return res;
    }

    void backtrack(int index, string &digits, string &opt)
    {
        if (opt.length() == digits.length()) {
            res.push_back(opt);
            return;
        }

        int num = digits[index] - '0';

        for (char c : dict[num]) {
            opt.push_back(c);
            backtrack(index + 1, digits, opt);
            opt.pop_back();  // backtrack
        }
    }
};