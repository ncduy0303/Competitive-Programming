#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

struct max_flow_graph {
    struct edge {
        int u, v, cap, flow;
    };
    int n; 
    vector<edge> el; 
    vector<vector<int>> adj;
    vector<int> dist, par;
    max_flow_graph(int n) : n(n), adj(n + 1) {}
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
        dist.assign(n + 1, INF);
        par.assign(n + 1, 0);
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
    ll edmonds_karp(int s, int e) {
        ll mf = 0;
        while (bfs(s, e)) mf += send_one_flow(s, e);
        return mf;
    }
    ll dinic(int s, int e) {
        ll mf = 0;
        while (bfs(s, e)) {
            while (int nf = dfs(s, e)) mf += nf;
        }
        return mf;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
}