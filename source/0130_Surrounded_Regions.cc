/* 130. Surrounded Regions */

#include <queue>
#include <vector>

using std::pair;
using std::queue;
using std::vector;

class Solution
{
    int ROWS, COLS;
    vector<vector<int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

public:
    void solve(vector<vector<char>> &board)
    {
        ROWS = board.size();
        COLS = board[0].size();

        capture(board);

        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLS; c++) {
                /*
                    surround case, change to 'X'
                */
                if (board[r][c] == 'O') {
                    board[r][c] = 'X';
                }
                /*
                    Not surround case, remain 'O'
                    - locate at the boarder
                    - neightbors position that connect to the boarder
                */
                else if (board[r][c] == 'T') {
                    board[r][c] = 'O';
                }
            }
        }
    }

private:
    // BFS
    void capture(vector<vector<char>> &board)
    {
        queue<pair<int, int>> q;
        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLS; c++) {
                /*
                    'O' located at the boarder,
                    push into queue not surround by 'X'
                */
                if (r == 0 || r == ROWS - 1 || c == 0 ||
                    c == COLS - 1 && board[r][c] == 'O') {
                    q.push({r, c});
                }
            }
        }
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            board[r][c] = 'T';

            // apply BFS to check four direction state
            for (const auto &dir : dirs) {
                int nr = r + dir[0];
                int nc = c + dir[1];
                // valid: pos locate in the grid and the value equal to '0'
                if (nr >= 0 && nc >= 0 && nr < ROWS && nc < COLS &&
                    board[nr][nc] == 'O')
                    q.push({nr, nc});
            }
        }
    }
};