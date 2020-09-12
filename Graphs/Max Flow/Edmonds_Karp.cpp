// Maximum Flow (Edmonds-Karp Algorithm)
// Time complexity: O(nm^2) in total, O(nm) BFS iterations with O(m) per BFS
// Reference: https://github.com/mochow13/competitive-programming-library/blob/master/Graph/Max%20Flow%20Edmond%20Karp.cpp
// Problem link: https://cses.fi/problemset/task/1694/

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

struct max_flow_graph {
    int V;
    struct edge {
        int src, dst, cap, res;
        size_t rev;
    };
    edge &rev(edge e) { 
        return adj[e.dst][e.rev]; 
    };
    vector<vector<edge>> adj;
    max_flow_graph(int V) : V(V), adj(V) {}
    void add_edge(int src, int dst, int cap) {
        adj[src].push_back({src, dst, cap, 0, adj[dst].size()});   // original edge
        adj[dst].push_back({dst, src, 0, 0, adj[src].size() - 1}); // residual back edge (notice cap = 0)
    }
    ll max_flow(int s, int t) {
        for (int u = 0; u < V; u++)
            for (auto &e : adj[u])
                e.res = e.cap;
        ll total = 0;
        while (true) {
            vector<int> prev(V, -1); prev[s] = -2;
            queue<int> q; q.push(s);
            while (!q.empty() && prev[t] == -1) {
                int u = q.front(); q.pop();
                for (edge &e : adj[u]) {
                    if (prev[e.dst] == -1 && e.res > 0) {
                        prev[e.dst] = e.rev;
                        q.push(e.dst);
                    }
                }
            }
            if (prev[t] == -1) break;
            int inc = INF;
            for (int u = t; u != s; u = adj[u][prev[u]].dst)
                inc = min(inc, rev(adj[u][prev[u]]).res);
            for (int u = t; u != s; u = adj[u][prev[u]].dst) {
                adj[u][prev[u]].res += inc;
                rev(adj[u][prev[u]]).res -= inc;
            }
            total += inc;
        }
        return total;
    }
};
 
void solve() {
    int n, m; cin >> n >> m;
    max_flow_graph adj(n);
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w; u--; v--;
        adj.add_edge(u, v, w);
    }
    cout << adj.max_flow(0, n - 1) << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int tc; tc = 1;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t  << ": ";
        solve();
    }
}