/* pascal triangle 20250903 */

#include <iostream>
#include <vector>

using std::vector;

vector<vector<int>> pac(int x)
{
    vector<vector<int>> res;
    for (int i = 1; i <= x; i++) {
        vector<int> a;
        for (int j = 1; j <= i; j++) {
            if (i == 1 || j == 1 || j == i) {
                a.push_back(1);
            } else {
                a.push_back(res[i - 2][j - 2] + res[i - 2][j - 1]);
            }
        }
        res.push_back(a);
    }
    return res;
};

/*
1.         (1,1)
1 1.       (2,1) (2,2)
1 2 1.     (3,1) (3,2) (3,3)
1 3 3 1    (4,1) (4,2) (4,3) (4,4)
1 4 6 4 1
1 5 10 5 1
1 6 15 15 6 1
1 7 21 30 21 7 1
*/

int main()
{
    vector<vector<int>> res = pac(10);
    for (const auto a : res) {
        for (const auto b : a) {
            std::cout << b << ", ";
        }
        std::cout << std::endl;
    }
}