/* 20. Valid Parentheses */

#include <stack>
#include <unordered_map>

class Solution
{
public:
    bool isValid(std::string s)
    {
        std::stack<char> st;
        std::unordered_map<char, char> hp = {
            {'(', ')'}, {'[', ']'}, {'{', '}'}};

        for (char c : s) {
            // when input char is '(' , '[', '{'
            if (hp.find(c) != hp.end())
                st.push(c);
            // when input char is ')' , ']', '}' but match to the st
            else if (!st.empty() && c == hp[st.top()])
                st.pop();
            // when input char is ')' , ']', '}' but not match to the st
            else if (!st.empty() && c != hp[st.top()])
                return false;
            // other, when st.empty() and input char is ')' , ']', '}'
            else
                st.push(c);
        }
        return st.empty() && true;
    }
};