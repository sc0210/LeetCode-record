/* 1046. Last Stone Weight */

#include <queue>
#include <vector>
using std::vector;

class Solution
{
public:
    int lastStoneWeight(vector<int> &stones)
    {
        std::priority_queue<int> pq(stones.begin(), stones.end());

        while (!pq.empty()) {
            int e1 = pq.top();
            pq.pop();
            if (pq.empty())  // only one element left
                return e1;
            int e2 = pq.top();
            pq.pop();

            if (e1 == e2)
                continue;
            else if (e1 > e2)
                pq.push(e1 - e2);
        }
        // no element left
        return 0;
    }
};
