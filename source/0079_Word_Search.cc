/* 79. Word Search */

#include <set>
#include <string>
#include <vector>

using std::set;
using std::string;
using std::vector;


class Solution
{
public:
    int ROWS, COLS;
    set<std::pair<int, int>> path;

    bool exist(vector<vector<char>> &board, string word)
    {
        ROWS = board.size();
        COLS = board[0].size();

        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLS; c++) {
                if (dfs(board, word, r, c, 0))
                    return true;
            }
        }
        return false;
    }

    bool dfs(vector<vector<char>> &board, string word, int r, int c, int i)
    {
        if (i == word.length())
            return true;
        /*
            invalid case:
            - out of bound
            - not match to word
            - already existed in the set
        */
        if (r < 0 || c < 0 || r >= ROWS || c >= COLS || board[r][c] != word[i])
            return false;

        // mark visited
        char tmp = board[r][c];
        board[r][c] = '#';

        // explore 4 directions
        bool found = dfs(board, word, r + 1, c, i + 1) ||
                     dfs(board, word, r - 1, c, i + 1) ||
                     dfs(board, word, r, c + 1, i + 1) ||
                     dfs(board, word, r, c - 1, i + 1);
        /*
            Restore state:
            erase is necessary to unmark the cell after recursion returns, so
            that other search paths can still use it.
         */
        board[r][c] = tmp;
        return found;
    }
};
