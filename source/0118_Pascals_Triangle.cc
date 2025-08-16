/* 118. Pascal's Triangle */

#include <vector>
using std::vector;

class Solution
{
public:
    vector<vector<int>> generate(int numRows)
    {
        // only 1 level
        vector<vector<int>> ans = {{1}};
        if (numRows == 1) {
            return ans;
        }

        // level 2, multi-level traverse
        for (int i = 2; i <= numRows; i++) {
            // single level traverse
            vector<int> level;
            level.push_back(1);
            for (int j = 1; j <= i - 2; j++) {
                level.push_back(ans[i - 2][j - 1] + ans[i - 2][j]);
            }
            level.push_back(1);

            // update ans vector
            ans.push_back(level);
        }

        return ans;
    }
};