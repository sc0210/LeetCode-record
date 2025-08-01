/* 787. Cheapest Flights Within K Stops */

#include <queue>
#include <vector>
using std::priority_queue;
using std::vector;
class Solution
{
    using tiii = std::tuple<int, int, int>;

public:
    int findCheapestPrice(int n,
                          vector<vector<int>> &flights,
                          int src,
                          int dst,
                          int k)
    {
        /*
            method1: Dijkstra's Algorithm
            Don't allow existed negative edge in the graph
         */
        int INF = 1e9;
        vector<vector<std::pair<int, int>>> adj(n);
        vector<vector<int>> dist(n, vector<int>(k + 5, INF));

        // setup adjacent matrix
        for (const auto &flight : flights) {
            int src = flight[0], dst = flight[1], cost = flight[2];
            adj[src].emplace_back(dst, cost);
        }

        dist[src][0] = 0;
        priority_queue<tiii, vector<tiii>, std::greater<tiii>> minHeap;
        minHeap.emplace(0, src, -1);

        while (!minHeap.empty()) {
            auto [cst, node, stops] = minHeap.top();
            minHeap.pop();
            // reach to the end, return the total cost
            if (node == dst) {
                return cst;
            }
            // when k stops or after adding next stop is less than cost
            if (stops == k || dist[node][stops + 1] < cst) {
                continue;
            }

            for (auto &[nei, w] : adj[node]) {
                int nextCst = cst + w;
                int nextStops = stops + 1;
                // update the negihbor edge when found les cost
                if (dist[nei][nextStops + 1] > nextCst) {
                    dist[nei][nextStops + 1] = nextCst;
                    minHeap.emplace(nextCst, nei, nextStops);
                }
            }
        }
        return -1;

        /*
            method2: Bellman Ford Algorithm
            Allow existed negative edge in the graph
        */
        vector<int> prices(n, INT_MAX);
        prices[src] = 0;  // set the source point to 0

        // at most k stops, each iteration update one stop
        for (int i = 0; i <= k; i++) {
            vector<int> tmpPrices = prices;

            for (const auto &flight : flights) {
                int src = flight[0], dst = flight[1], cost = flight[2];

                // node that haven't been discovered
                if (prices[src] == INT_MAX) {
                    continue;
                }
                // when found a node that have lower cost, replace it
                if (prices[src] + cost < tmpPrices[dst]) {
                    tmpPrices[dst] = prices[src] + cost;
                }
            }

            // update the price vector
            prices = tmpPrices;
        }

        return prices[dst] == INT_MAX ? -1 : prices[dst];
    }
};
