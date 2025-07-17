/* 210. Course Schedule II */
#include <queue>
#include <vector>

using std::queue;
using std::vector;

class Solution
{
public:
    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
    {
        vector<int> inDegree(numCourses, 0);
        vector<vector<int>> adj(numCourses);

        for (auto val : prerequisites) {
            int PreCourse = val[1], NextCourse = val[0];
            inDegree[PreCourse]++;
            adj[NextCourse].emplace_back(PreCourse);
        }

        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (inDegree[i] == 0)
                q.push(i);
        }

        int finish = 0;
        vector<int> ans(numCourses);
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            ans[numCourses - finish - 1] = node;
            finish++;

            for (auto nei : adj[node]) {
                inDegree[nei]--;
                if (inDegree[nei] == 0)
                    q.push(nei);
            }
        }

        if (finish != numCourses)
            return {};
        return ans;
    }
};