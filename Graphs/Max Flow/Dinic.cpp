// Maximum Flow (Dinic Algorithm)
// Time complexity: O(n^2m)
// A slight improvement from Edmonds_Karp Algorithm
// Problem link: https://cses.fi/problemset/task/1694/

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 5;
const ll MOD = 1e9 + 7;
const ll INF = 1e18;

struct max_flow_graph {
    struct edge {
        int u, v, cap, flow;
    };
    int n; 
    vector<edge> el; 
    vector<vector<int>> adj;
    vector<int> dist, par;
    max_flow_graph(int n) : n(n), adj(n) {}
    void add_edge(int u, int v, int w) {
        adj[u].push_back(el.size());
        el.push_back({u, v, w, 0});
        adj[v].push_back(el.size());
        el.push_back({v, u, 0, 0}); 
    }
    int send_one_flow(int s, int e) {
        int nf = INF;
        for (int u = e; u != s; u = el[par[u]].u) {
            nf = min(nf, el[par[u]].cap - el[par[u]].flow);
        }
        for (int u = e; u != s; u = el[par[u]].u) {
            el[par[u]].flow += nf;
            el[par[u]^1].flow -= nf;
        }
        return nf;
    }
    bool bfs(int s, int e) {
        dist.assign(n, INF);
        par.assign(n, 0);
        queue<int> q;
        q.push(s); dist[s] = 0;
        while (q.size()) {
            int u = q.front(); q.pop();
            if (u == e) break;
            for (int idx : adj[u]) {
                if (el[idx].cap > el[idx].flow && dist[el[idx].v] > dist[el[idx].u] + 1) {
                    dist[el[idx].v] = dist[el[idx].u] + 1;
                    par[el[idx].v] = idx;
                    q.push(el[idx].v);
                }
            }
        }
        return dist[e] < INF;
    }
    int dfs(int s, int e, int f = INF) {
        if (s == e || f == 0) return f;
        for (int idx : adj[s]) {
            if (dist[el[idx].v] != dist[s] + 1) continue;
            if (int nf = dfs(el[idx].v, e, min(f, el[idx].cap - el[idx].flow))) {
                el[idx].flow += nf;
                el[idx^1].flow -= nf;
                return nf;
            }
        }
        return 0;
    }
    ll dinic(int s, int e) {
        ll mf = 0;
        while (bfs(s, e)) {
            while (int nf = dfs(s, e)) mf += nf;
        }
        return mf;
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
    int tc = 1;
    // cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t << ": ";
        solve();
    }
}