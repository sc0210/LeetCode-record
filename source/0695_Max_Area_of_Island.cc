#include <queue>
#include <vector>

using std::queue;
using std::vector;

class Solution
{
public:
    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    int maxAreaOfIsland(vector<vector<int>> &grid)
    {
        int maxArea = INT_MIN, currArea = 0;

        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == 1) {
                    // 1 for the current step is '1'
                    currArea = 1 + bfs(grid, i, j);
                }
                maxArea = std::max(maxArea, currArea);
            }
        }
        return maxArea;
    }

    int bfs(vector<vector<int>> &grid, int r, int c)
    {
        int currArea = 0;
        queue<std::pair<int, int>> q;
        q.push({r, c});
        grid[r][c] = 0;

        while (!q.empty()) {
            // Pop the first element in the queue
            int r = q.front().first;
            int c = q.front().second;
            q.pop();

            // Search in four directions (up, down, left, right)
            for (int i = 0; i < 4; i++) {
                int row = r + directions[i][0];
                int col = c + directions[i][1];
                if (row >= 0 && row < grid.size() && col >= 0 &&
                    col < grid[0].size() && grid[row][col] == 1) {
                    q.push({row, col});
                    grid[row][col] = 0;
                    currArea++;
                }
            }
        }
        return currArea;
    }
};