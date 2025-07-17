/* 743 Network Delay Time */
#include <queue>
#include <vector>
using std::pair;
using std::vector;

class Solution
{
public:
    int networkDelayTime(vector<vector<int>> &times, int n, int k)
    {
        using P = pair<int, int>;
        vector<vector<P>> adj(n + 1);
        int e = times.size();
        for (int i = 0; i < e; i++) {
            int u = times[i][0];
            int v = times[i][1];
            int w = times[i][2];
            adj[u].push_back({v, w});
        }

        // Applying Dijkstra
        vector<int> dist(n + 1, INT_MAX);
        dist[k] = 0;
        std::priority_queue<P, vector<P>, std::greater<P>> pq;
        pq.push({0, k});
        while (!pq.empty()) {
            int distance = pq.top().first;
            int node = pq.top().second;
            pq.pop();
            for (auto i : adj[node]) {
                int child = i.first;
                int child_dist = i.second;

                if (distance + child_dist < dist[child]) {
                    dist[child] = distance + child_dist;
                    pq.push({dist[child], child});
                }
            }
        }

        int minTime = 0;
        for (int i = 1; i <= n; i++) {
            if (dist[i] == INT_MAX)
                return -1;
            if (minTime < dist[i])
                minTime = dist[i];
        }

        return minTime;
    }
};