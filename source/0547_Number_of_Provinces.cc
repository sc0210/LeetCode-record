/* 547. Number of Provinces */

#include <queue>
#include <unordered_set>
#include <vector>


class DSU
{
    std::vector<int> parent, rank;

public:
    DSU(int n)
    {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x)
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]);  // path compression
        return parent[x];
    }

    void unite(int x, int y)
    {
        int px = find(x), py = find(y);
        if (px == py)
            return;
        if (rank[px] < rank[py]) {
            parent[px] = py;
        } else if (rank[px] > rank[py]) {
            parent[py] = px;
        } else {
            parent[py] = px;
            rank[px]++;
        }
    }
};

class Solution
{
public:
    // int findCircleNum(std::vector<std::vector<int>> &isConnected)
    // {
    //     int N = isConnected.size();
    //     std::vector<bool> visited(N, false);
    //     int part = 0;

    //     for (int i = 0; i < N; i++) {
    //         if (!visited[i]) {
    //             part++;
    //             // BFS from node i
    //             std::queue<int> q;
    //             q.push(i);
    //             visited[i] = true;

    //             while (!q.empty()) {
    //                 int cur = q.front();
    //                 q.pop();

    //                 for (int nei = 0; nei < N; nei++) {
    //                     if (isConnected[cur][nei] && !visited[nei]) {
    //                         visited[nei] = true;
    //                         q.push(nei);
    //                     }
    //                 }
    //             }
    //         }
    //     }
    //     return part;
    // }

    // DSU (Disjoint Set Union / Union-Find)
    int findCircleNum(std::vector<std::vector<int>> &isConnected)
    {
        int N = isConnected.size();
        DSU dsu(N);

        // union all connected nodes
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                if (isConnected[i][j]) {
                    dsu.unite(i, j);
                }
            }
        }

        // count unique parents
        std::unordered_set<int> provinces;
        for (int i = 0; i < N; i++) {
            provinces.insert(dsu.find(i));
        }

        return provinces.size();
    }
};