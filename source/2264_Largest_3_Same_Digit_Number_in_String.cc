/* 2264. Largest 3-Same-Digit Number in String */

#include <string>

class Solution
{
public:
    std::string largestGoodInteger(std::string num)
    {
        int maxVal = -1;
        for (int i = 0; i < num.size() - 2; i++) {
            // valid case, contiguous sequence of characters three char is same
            if (num[i] == num[i + 1] && num[i + 1] == num[i + 2]) {
                int curVal = 100 * (num[i] - '0') + 10 * (num[i + 1] - '0') +
                             (num[i + 2] - '0');
                maxVal = std::max(maxVal, curVal);
                // cout << num[i] << num[i+1] << num[i+2] << " ";
                // cout << maxVal << " " << curVal << endl;
            }
        }
        // handle edge case "0", return "000"
        if (maxVal == 0)
            return "000";
        // not getting valid vase, return ""
        else if (maxVal == -1)
            return "";
        // others, return the res in string format
        return std::to_string(maxVal);
    }
};