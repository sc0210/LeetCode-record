/* 417. Pacific Atlantic Water Flow */

#include <queue>
#include <vector>

using std::pair;
using std::queue;
using std::vector;

class Solution
{
    vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>> &heights)
    {
        int ROWS = heights.size(), COLS = heights[0].size();
        vector<vector<bool>> pac(ROWS, vector<bool>(COLS, false));
        vector<vector<bool>> atl(ROWS, vector<bool>(COLS, false));

        queue<pair<int, int>> pacQueue, atlQueue;

        for (int c = 0; c < COLS; ++c) {
            pacQueue.push({0, c});
            atlQueue.push({ROWS - 1, c});
            // dfs(0, c, pac, heights);
            // dfs(ROWS - 1, c, atl, heights);
        }
        for (int r = 0; r < ROWS; ++r) {
            pacQueue.push({r, 0});
            atlQueue.push({r, COLS - 1});
            // dfs(r, 0, pac, heights);
            // dfs(r, COLS - 1, atl, heights);
        }

        bfs(pacQueue, pac, heights);
        bfs(atlQueue, atl, heights);

        vector<vector<int>> res;
        for (int r = 0; r < ROWS; ++r) {
            for (int c = 0; c < COLS; ++c) {
                if (pac[r][c] && atl[r][c]) {
                    res.push_back({r, c});
                }
            }
        }
        return res;
    }

private:
    void bfs(queue<pair<int, int>> &q,
             vector<vector<bool>> &ocean,
             vector<vector<int>> &heights)
    {
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            ocean[r][c] = true;
            for (auto [dr, dc] : directions) {
                int nr = r + dr, nc = c + dc;
                if (nr >= 0 && nr < heights.size() && nc >= 0 &&
                    nc < heights[0].size() && !ocean[nr][nc] &&
                    heights[nr][nc] >= heights[r][c]) {
                    q.push({nr, nc});
                }
            }
        }
    }

    void dfs(int r,
             int c,
             vector<vector<bool>> &ocean,
             vector<vector<int>> &heights)
    {
        ocean[r][c] = true;
        for (auto [dr, dc] : directions) {
            int nr = r + dr, nc = c + dc;
            if (nr >= 0 && nr < heights.size() && nc >= 0 &&
                nc < heights[0].size() && !ocean[nr][nc] &&
                heights[nr][nc] >= heights[r][c]) {
                dfs(nr, nc, ocean, heights);
            }
        }
    }
};