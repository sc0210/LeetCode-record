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
        using pii = pair<int, int>;
        vector<vector<pii>> adj(n + 1);
        int e = times.size();
        for (int i = 0; i < e; i++) {
            int u = times[i][0];
            int v = times[i][1];
            int w = times[i][2];
            adj[u].push_back({v, w});
        }

        // Dijkstra algorithm (single source to all vertex problem)

        // dist[]: a vector store the minimial cost from given node to each node
        vector<int> dist(n + 1, INT_MAX);
        dist[k] = 0;  // set start point

        // pq: to get the minimal value for each edge
        std::priority_queue<pii, vector<pii>, std::greater<pii>> pq;
        pq.push({0, k});

        while (!pq.empty()) {
            auto [dis, node] = pq.top();
            pq.pop();

            // update nei_node (relax)
            for (auto &nei : adj[node]) {
                auto [nei_node, weight] = nei;
                // weight: node <-> nei_node
                if (dist[node] + weight < dist[nei_node]) {
                    dist[nei_node] = dist[node] + weight;
                    // add nei_node into pq for further calculation
                    pq.push({dist[nei_node], nei_node});
                }
            }
        }

        int minTime = 0;
        for (int i = 1; i <= n; i++) {
            // if existed node cannot reach by the given node k
            if (dist[i] == INT_MAX) {
                return -1;
            }
            // update the minTime when get larger delay time
            if (dist[i] > minTime) {
                minTime = dist[i];
            }
        }

        return minTime;
    }
};