// Maximum Flow (Dinic Algorithm)
// Time complexity: O(n^2m)
// A slight improvement from Edmonds_Karp Algorithm
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
    vector<ar<ll,3>> edges; // {dest, cap, flow}
    vector<vector<int>> adj;
    vector<int> dist, last;
    vector<ar<int,2>> par;
    max_flow_graph(int V): V(V), adj(V) {}
    void add_edge(int u, int v, int w) {
        adj[u].push_back(edges.size());
        edges.push_back({v, w, 0});
        adj[v].push_back(edges.size());
        edges.push_back({u, 0, 0});
    }
    bool bfs(int s, int t) {
        dist.assign(V, -1);
        par.assign(V, {-1, -1});
        queue<int> q;
        dist[s] = 0; q.push(s);
        while (q.size()) {
            int u = q.front(); q.pop();
            if (u == t) break;
            for (int idx : adj[u]) {
                auto [v, cap, flow] = edges[idx];
                if (cap > flow && dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    par[v] = {u, idx};
                    q.push(v);
                }
            }
        }
        return dist[t] != -1;
    }
    ll send_one_flow(int s, int t) {
        ll new_flow = INF;
        for (int u = t; u != s; u = par[u][0]) {
            int idx = par[u][1];
            auto [v, cap, flow] = edges[idx];
            new_flow = min(new_flow, cap - flow);
        }
        for (int u = t; u != s; u = par[u][0]) {
            int idx = par[u][1];
            auto [v, cap, flow] = edges[idx];
            edges[idx][2] += new_flow;
            edges[idx ^ 1][2] -= new_flow;
        }
        return new_flow;
    }
    ll dfs(int s, int t, ll f = INF) {
        if (s == t || f == 0) return f;
        for (int i = last[s]; i < adj[s].size(); i++) {
            int idx = adj[s][i];
            auto [v, cap, flow] = edges[idx];
            if (dist[v] != dist[s] + 1) continue;
            if (ll new_flow = dfs(v, t, min(f, cap - flow))) {
                edges[idx][2] += new_flow;
                edges[idx ^ 1][2] -= new_flow;
                return new_flow;
            }
        }
        return 0;
    }
    ll dinic(int s, int t) {
        ll max_flow = 0;
        while (bfs(s, t)) {
            last.assign(V, 0);
            while (ll new_flow = dfs(s, t)) max_flow += new_flow;
        }
        return max_flow;
    }
};

void solve() {
    int n, m; cin >> n >> m;
    max_flow_graph adj(n);
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w; u--; v--;
        adj.add_edge(u, v, w);
    }
    cout << adj.dinic(0, n - 1) << "\n";
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