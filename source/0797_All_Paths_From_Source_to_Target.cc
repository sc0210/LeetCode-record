/* 797. All Paths From Source to Target */

#include <vector>
using std::vector;

class Solution
{
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>> &graph)
    {
        vector<vector<int>> result;
        vector<int> path;

        path.push_back(0);  // Start with source
        dfs(graph, 0, path, result);
        return result;
    }

    void dfs(vector<vector<int>> &graph,
             int node,
             vector<int> &path,
             vector<vector<int>> &result)
    {
        // Base case: Reached the target
        if (node == graph.size() - 1) {
            result.push_back(path);  // Save current path
        }

        // Explore neighbors
        for (int nei : graph[node]) {
            path.push_back(nei);            // Choose
            dfs(graph, nei, path, result);  // DFS
            path.pop_back();                // Backtrack
        }
    }
};