/* 14. Longest Common Prefix */
#include <string>
#include <vector>

using std::string;
using std::vector;

class Solution
{
public:
    string longestCommonPrefix(vector<string> &strs)
    {
        int N = strs.size();
        string common = "";

        string minElement = strs[0];
        for (int i = 0; i < N; i++) {
            if (strs[i].size() < minElement.size()) {
                minElement = strs[i];
            }
        }
        for (int minIndex = 0; minIndex < minElement.size(); minIndex++) {
            int match = true;
            for (int wordIndex = 0; wordIndex < N; wordIndex++) {
                // when there are word's prefix not match
                if (minElement[minIndex] != strs[wordIndex][minIndex]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                // when match, start next iteration
                common += minElement[minIndex];
            } else {
                // when not match, stop
                break;
            }
        }
        return common;
    }
};