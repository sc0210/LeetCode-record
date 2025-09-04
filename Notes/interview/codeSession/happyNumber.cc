/* happy numeber 20250903 */

#include <iostream>
#include <unordered_set>

using std::cout;
using std::endl;
using std::unordered_set;

bool ishappy(int n, unordered_set<int> &record)
{
    if (n == 1)
        return true;

    int sum = 0;
    while (n) {
        int rem = n % 10;
        sum += (rem * rem);
        n /= 10;
    }

    // if the calculate is exsited berforehand, exit, not a happy number
    if (record.count(sum)) {
        return false;
    } else {
        // record the calculated value and recursive calculated
        // cout << sum << " ";
        record.insert(sum);
        return ishappy(sum, record);  // recursive call
    }
};

void helper(int n, unordered_set<int> &record)
{
    record.clear();
    if (ishappy(n, record)) {
        cout << n << " is a happy number." << endl;
    } else {
        cout << n << " is not a happy number." << endl;
    }
};

int main()
{
    unordered_set<int> record;
    helper(397, record);
    helper(145, record);
    helper(19, record);
    helper(2, record);
    return 0;
};


/*
2: 4
4: 16
16: 1+36=37
37: 9+49=58
58: 25+64=89
89: 64+81=145
145: 1+16+25=42
42: 16+4=20
20: 4


19: 1+81=82
82: 64+4=68
68: 36+64=100
100: 1
1
*/