# Graph Algorithms Cheatsheet (C++)

## 1. 判斷圖是否為樹

> 圖有 N 個節點與 N-1 條邊且連通

```cpp
bool validTree(int n, vector<vector<int>>& edges) {
    if (edges.size() != n - 1) return false;
    vector<vector<int>> graph(n);
    for (auto& e : edges) {
        graph[e[0]].push_back(e[1]);
        graph[e[1]].push_back(e[0]);
    }
    vector<bool> visited(n, false);
    queue<int> q{{0}};
    visited[0] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : graph[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    return all_of(visited.begin(), visited.end(), [](bool v) { return v; });
}
```

## 2. 找出圖中連通分量數量

> 使用 DFS 標記造訪過的節點

```cpp
void dfs(int u, vector<vector<int>>& g, vector<bool>& vis) {
    vis[u] = true;
    for (int v : g[u]) if (!vis[v]) dfs(v, g, vis);
}
int countComponents(int n, vector<vector<int>>& edges) {
    vector<vector<int>> g(n);
    for (auto& e : edges) g[e[0]].push_back(e[1]), g[e[1]].push_back(e[0]);
    vector<bool> vis(n);
    int count = 0;
    for (int i = 0; i < n; ++i)
        if (!vis[i]) dfs(i, g, vis), count++;
    return count;
}
```

## 3. 判斷是否為二分圖 (Bipartite)

> BFS 塗色，相鄰節點不可同色

```cpp
bool isBipartite(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> color(n, -1);
    for (int i = 0; i < n; ++i) {
        if (color[i] != -1) continue;
        queue<int> q{{i}}; color[i] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : graph[u]) {
                if (color[v] == -1) color[v] = 1 - color[u], q.push(v);
                else if (color[v] == color[u]) return false;
            }
        }
    }
    return true;
}
```

## 4. 拓撲排序

### (1) Kahn’s Algorithm

> BFS 配合 indegree 陣列
```cpp
vector<int> topoSort(int n, vector<vector<int>>& edges) {
    vector<vector<int>> g(n);
    vector<int> indeg(n), order;
    for (auto& e : edges) g[e[0]].push_back(e[1]), indeg[e[1]]++;
    queue<int> q;
    for (int i = 0; i < n; ++i) if (indeg[i] == 0) q.push(i);
    while (!q.empty()) {
        int u = q.front(); q.pop(); order.push_back(u);
        for (int v : g[u]) if (--indeg[v] == 0) q.push(v);
    }
    return order.size() == n ? order : vector<int>{};
}
```

### (2) DFS + Postorder

> 拓樹反向後序排列

```cpp
void dfsTopo(int u, vector<vector<int>>& g, vector<bool>& vis, vector<int>& res) {
    vis[u] = true;
    for (int v : g[u]) if (!vis[v]) dfsTopo(v, g, vis, res);
    res.push_back(u);
}
vector<int> topoSortDFS(int n, vector<vector<int>>& edges) {
    vector<vector<int>> g(n);
    for (auto& e : edges) g[e[0]].push_back(e[1]);
    vector<bool> vis(n);
    vector<int> res;
    for (int i = 0; i < n; ++i) if (!vis[i]) dfsTopo(i, g, vis, res);
    reverse(res.begin(), res.end());
    return res;
}
```

## 5. 最短路徑

### Dijkstra

> 適用無負權圖，用最小堆更新距離

```cpp
vector<int> dijkstra(int n, vector<vector<pair<int, int>>>& g, int src) {
    vector<int> dist(n, INT_MAX); dist[src] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, src});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto& [v, w] : g[u]) if (dist[u] + w < dist[v])
            dist[v] = dist[u] + w, pq.push({dist[v], v});
    }
    return dist;
}
```

### Bellman-Ford

> 適用有負權圖，最多跑 N-1 輪

```cpp
vector<int> bellmanFord(int n, vector<vector<int>>& edges, int src) {
    vector<int> dist(n, INT_MAX); dist[src] = 0;
    for (int i = 0; i < n - 1; ++i)
        for (auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            if (dist[u] != INT_MAX && dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
        }
    return dist;
}
```

### Floyd-Warshall

> 適用 All-Pairs 最短路

```cpp
vector<vector<int>> floyd(int n, vector<vector<int>>& graph) {
    auto dist = graph;
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    return dist;
}
```

## 6. 最小生成樹 MST

### Prim

> 選最小邊擴張，類似 Dijkstra

```cpp
int prim(int n, vector<vector<pair<int, int>>>& g) {
    vector<bool> vis(n);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, 0});
    int total = 0;
    while (!pq.empty()) {
        auto [w, u] = pq.top(); pq.pop();
        if (vis[u]) continue;
        vis[u] = true; total += w;
        for (auto& [v, cost] : g[u]) if (!vis[v]) pq.push({cost, v});
    }
    return total;
}
```

### Kruskal + Union-Find

> 按邊權排序加入，不成環

```cpp
struct DSU {
    vector<int> p;
    DSU(int n) : p(n) { iota(p.begin(), p.end(), 0); }
    /* 
        iota(): Fills the range [first, last) with sequentially increasing values,
             starting with value and repetitively evaluating ++value.
    */
    int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
    bool unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return false;
        p[rx] = ry;
        return true;
    }
};
int kruskal(int n, vector<vector<int>>& edges) {
    sort(edges.begin(), edges.end(), [](auto& a, auto& b) { return a[2] < b[2]; });
    DSU dsu(n);
    int total = 0;
    for (auto& e : edges)
        if (dsu.unite(e[0], e[1])) total += e[2];
    return total;
}
```
