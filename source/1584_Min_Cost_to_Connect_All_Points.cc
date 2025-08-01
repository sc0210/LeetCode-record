/* 1584. Min Cost to Connect All Points */

#include <algorithm>
#include <queue>
#include <unordered_set>
#include <vector>
using std::priority_queue;
using std::unordered_set;
using std::vector;

class DSU
{
public:
    vector<int> Parent, Size;

    DSU(int n) : Parent(n + 1), Size(n + 1, 1)
    {
        // initialization, set all the parent to itself
        for (int i = 0; i <= n; ++i) {
            Parent[i] = i;
        }
    }

    int find(int node)
    {
        if (Parent[node] != node) {
            Parent[node] = find(Parent[node]);
        }
        return Parent[node];
    }

    bool unionSets(int u, int v)
    {
        int pu = find(u), pv = find(v);
        // if parent are the same, return false
        if (pu == pv) {
            return false;
        }
        // Make sure that pu size is always larger than pz
        if (Size[pu] < Size[pv]) {
            std::swap(pu, pv);
        }
        // update pu size, since we modify the pv parent to pu
        Size[pu] += Size[pv];
        Parent[pv] = pu;
        return true;
    }
};

class Solution
{
    using pii = std::pair<int, int>;

public:
    int minCostConnectPoints(vector<vector<int>> &points)
    {
        /*
            method1: Kruskal's Algorithm, Disjoint set union

            In each iteration, fetch the min. cost edge from all edge to
            merge. When the merge contain loop(invalid), then discard it. Until
            all the edge(node number - 1) is create
        */
        int n = points.size();
        DSU dsu(n);
        vector<std::tuple<int, int, int>> edges;

        // initialization, create edge info
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int dist = abs(points[i][0] - points[j][0]) +
                           abs(points[i][1] - points[j][1]);
                edges.push_back({dist, i, j});
            }
        }
        // sort all the edge from small to large
        std::sort(edges.begin(), edges.end(), [](const auto &a, const auto &b) {
            return std::get<0>(a) < std::get<1>(b);  // sort by `i`
        });

        // cost of the M.S.T.
        int res = 0;
        for (auto &[dist, u, v] : edges) {
            // add the edge if it don't create a cycle
            if (dsu.unionSets(u, v)) {
                res += dist;
            }
        }
        return res;


        /*
            method2: Prim's Algorithm

            In each iteration, fetch the min. cost edge from visied node to
            merge. When the merge contain loop(invalid), then discard it. Until
            all the edge(node number - 1) is create
        */
        int N = points.size();
        std::unordered_map<int, vector<pii>> adj;

        // use adjacent list to store edge infomation
        for (int i = 0; i < N; ++i) {
            int x1 = points[i][0];
            int y1 = points[i][1];
            for (int j = i + 1; j < N; ++j) {
                int x2 = points[j][0];
                int y2 = points[j][1];
                int dist = abs(x1 - x2) + abs(y1 - y2);
                adj[i].push_back({dist, j});
                adj[j].push_back({dist, i});
            }
        }

        res = 0;
        unordered_set<int> visited;
        priority_queue<pii, vector<pii>, std::greater<pii>> minH;
        minH.push({0, 0});  // {cost, node index}

        while (visited.size() < N) {
            // get the min. cost edge into M.S.T.
            auto curr = minH.top();
            minH.pop();
            int cost = curr.first;
            int i = curr.second;

            // if the node already visited, skip to next iteration
            if (visited.count(i)) {
                continue;
            }
            // else, not visited, update the cost
            res += cost;
            visited.insert(i);

            // update the neighbor edge of current node i,
            // add to PQ when the node index is not visited
            for (const auto &nei : adj[i]) {
                int neiCost = nei.first;
                int neiIndex = nei.second;
                if (!visited.count(neiIndex)) {
                    minH.push({neiCost, neiIndex});
                }
            }
        }

        return res;
    }
};
