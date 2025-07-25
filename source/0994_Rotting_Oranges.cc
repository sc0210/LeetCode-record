/* 994. Rotting Oranges */
#include <queue>
#include <vector>

using std::queue;
using std::vector;

class Solution
{
public:
    int orangesRotting(vector<vector<int>> &grid)
    {
        queue<std::pair<int, int>> q;
        int fresh = 0, time = 0;

        // calculate all the fresh, rotten keep int queue
        for (int r = 0; r < grid.size(); r++) {
            for (int c = 0; c < grid[0].size(); c++) {
                if (grid[r][c] == 1)
                    fresh++;
                if (grid[r][c] == 2)
                    q.push({r, c});
            }
        }

        vector<std::pair<int, int>> directions = {
            {0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        while (fresh > 0 && !q.empty()) {
            int length = q.size();
            // iterate all the rotten fruit
            for (int i = 0; i < length; i++) {
                int r = q.front().first;
                int c = q.front().second;
                q.pop();

                // check each directions of the rotten fruit
                for (const auto &dir : directions) {
                    int row = dir.first + r;
                    int col = dir.second + c;
                    // check the fruit is valid (inside the grid, fresh)
                    if (row >= 0 && row < grid.size() && col >= 0 &&
                        col < grid[0].size() && grid[row][col] == 1) {
                        grid[row][col] = 2;  // become rotten fruit
                        fresh--;             // decrease the fresh fruit size
                        q.push({row, col});  // add into rotten fruit queue
                    }
                }
            }
            time++;
        }
        return (fresh == 0) ? time : -1;
    }
};