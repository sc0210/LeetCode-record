/* 131. Palindrome Partitioning */

#include <string>
#include <vector>

using std::string;
using std::vector;

class Solution
{
    vector<vector<string>> res;

public:
    vector<vector<string>> partition(string s)
    {
        vector<string> path;
        backtrack(s, 0, path);
        return res;
    }

    void backtrack(const string &s, int start, vector<string> &path)
    {
        // 1. Termination condition
        if (start == s.size()) {
            res.push_back(path);
            return;
        }

        // 2. Explore choices
        for (int end = start; end < s.size(); end++) {
            // check if s[start..end] is palindrome
            if (isPali(s, start, end)) {
                path.push_back(s.substr(start, end - start + 1));
                backtrack(s, end + 1, path);
                path.pop_back();  // undo choice
            }
        }
    }

    bool isPali(const string &s, int l, int r)
    {
        while (l < r) {
            if (s[l] != s[r])
                return false;
            l++;
            r--;
        }
        return true;
    }
};
