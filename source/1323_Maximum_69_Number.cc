/* 1323. Maximum 69 Number */

#include <vector>

class Solution
{
public:
    int maximum69Number(int num)
    {
        std::vector<int> vec;
        int tmp = num;
        while (tmp) {
            vec.push_back(tmp % 10);
            tmp /= 10;
        }

        reverse(vec.begin(), vec.end());

        int maxVal = num, update_val, digit = vec.size();
        for (int i = 0; i < vec.size(); i++) {
            // iterate through the string, find the position of 6
            if (vec[i] == 6) {
                /*
                    calculate wether if gain greater value
                    when shift one digit from 6 to 9, limit max. to 9999
                */
                update_val = num + 3 * (pow(10, (digit - i - 1)));
                update_val = update_val > 9999 ? 9999 : update_val;
                maxVal = std::max(maxVal, update_val);
            }
        }
        return maxVal;
    }
};