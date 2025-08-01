/* 207. Course Schedule */
#include <queue>
#include <vector>

using std::vector;

class Solution
{
public:
    bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
    {
        vector<vector<int>> Adj(numCourses);
        vector<int> inDegree(numCourses, 0);
        /*
            Initialization (PreCourse: adjacent list, inDegree: vector)
            PreCourse <- NextCourse, complete PreCourse then NextCourse
        */
        for (const auto item : prerequisites) {
            int PreCourse = item[1];
            int NextCourse = item[0];
            inDegree[PreCourse]++;
            Adj[NextCourse].emplace_back(PreCourse);
        }


        /*
            when inDegree[i]==0 represent finish preCourse,
            add it into queue,
        */
        std::queue<int> q;

        for (int i = 0; i < numCourses; i++) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }

        int finish = 0;
        while (!q.empty()) {
            int curCourse = q.front();
            q.pop();
            finish++;

            for (const auto PreCourse : Adj[curCourse]) {
                inDegree[PreCourse]--;
                if (inDegree[PreCourse] == 0)
                    q.push(PreCourse);
            }
        }
        return finish == numCourses;
    }
};