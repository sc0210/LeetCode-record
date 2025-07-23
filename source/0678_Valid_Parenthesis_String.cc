/* 678. Valid Parenthesis String */

#include <stack>
#include <string>

class Solution
{
public:
    bool checkValidString(std::string s)
    {
        std::stack<int> open, star;
        // store index in the stack

        for (int i = 0; i < s.size(); ++i) {
            char c = s[i];
            if (c == '(') {
                open.push(i);
            } else if (c == '*') {
                star.push(i);
            } else if (c == ')') {
                // first lookup if existed '('
                if (!open.empty())
                    open.pop();
                // then check if existed '*'
                else if (!star.empty())
                    star.pop();
                // falied to close the paraenthesis
                else
                    return false;
            }
        }

        // Match remaining '(' with '*' from right to left
        while (!open.empty() && !star.empty()) {
            if (open.top() < star.top()) {
                open.pop();
                star.pop();
            } else {
                return false;  // '(' 出現在 '*' 之後，無法匹配
            }
        }

        return open.empty();
    }
};
