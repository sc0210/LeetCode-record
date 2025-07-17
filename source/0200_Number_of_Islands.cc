class Solution
{
public:
    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    int numIslands(vector<vector<char>> &grid)
    {
        int ROWS = grid.size();
        int COLS = grid[0].size();
        int island = 0;

        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (grid[i][j] == '1') {
                    // dfs(grid, i, j);
                    bfs(grid, i, j);
                    island++;
                }
            }
        }
        return island;
    }

    void dfs(vector<vector<char>> &grid, int r, int c)
    {
        if (r < 0 || c < 0 || r >= grid.size() || c >= grid[0].size() ||
            grid[r][c] == '0')
            return;

        grid[r][c] = '0';  // mark the adjenct 1s to 0, visited
        for (int i = 0; i < 4; i++) {
            // dfs to find the other four directions
            dfs(grid, r + directions[i][0], c + directions[i][1]);
        }
    }

    void bfs(vector<vector<char>> &grid, int r, int c)
    {
        queue<pair<int, int>> q;
        q.push({r, c});
        grid[r][c] = 0;  // mark as visited for current node

        while (!q.empty()) {
            auto node = q.front();
            q.pop();
            int rol = node.first;
            int col = node.second;
            for (int i = 0; i < 4; i++) {
                int nr = rol + directions[i][0];
                int nc = col + directions[i][1];
                if (nr >= 0 && nc >= 0 && nr < grid.size() &&
                    nc < grid[0].size() && grid[nr][nc] == '1') {
                    q.push({nr, nc});
                    grid[nr][nc] = '0';
                }
            }
        }
    }
};