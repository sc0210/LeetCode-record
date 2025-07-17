/* 207. Course Schedule */
#include <queue>
#include <vector>

using std::queue;
using std::vector;

class Solution
{
public:
    bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
    {
        // initialization(preCurse:adjacent list, inDegree:vector )
        vector<vector<int>> Adj(numCourses);
        vector<int> inDegree(numCourses, 0);

        for (auto item : prerequisites) {
            int PreCourse = item[1], NextCourse = item[0];
            inDegree[PreCourse]++;
            Adj[NextCourse].emplace_back(PreCourse);
        }

        // queue
        queue<int> q;
        for (int i = 0; i < numCourses; i++)
            if (inDegree[i] == 0)
                q.push(i);

        int finish = 0;
        while (!q.empty()) {
            int curCourse = q.front();
            q.pop();
            finish++;

            for (auto PreCourse : Adj[curCourse]) {
                inDegree[PreCourse]--;
                if (inDegree[PreCourse] == 0)
                    q.push(PreCourse);
            }
        }
        return finish == numCourses;
    }
};