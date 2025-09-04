/* 621. Task Scheduler */

#include <queue>
#include <vector>
using std::pair;
using std::priority_queue;
using std::queue;
using std::vector;

class Solution
{
public:
    int leastInterval(vector<char> &tasks, int n)
    {
        vector<int> count(26, 0);
        for (const char &task : tasks) {
            count[task - 'A']++;
        }

        priority_queue<int> maxHeap;
        for (const int &cnt : count) {
            if (cnt)
                maxHeap.push(cnt);
        }

        int time = 0;
        queue<pair<int, int>> q;
        while (!maxHeap.empty() || !q.empty()) {
            time++;

            if (maxHeap.empty())
                // maxHeap is empty
                time = q.front().second;
            else {
                // get the most freqency character, minus 1
                int cnt = maxHeap.top() - 1;
                maxHeap.pop();
                // remain element for that character, add the next show up time
                if (cnt)
                    q.push({cnt, time + n});
            }

            // when the waiting time is reach pop out, update maxHeap
            if (!q.empty() && q.front().second == time) {
                maxHeap.push(q.front().first);
                q.pop();
            }
        }
        return time;
    }
};
