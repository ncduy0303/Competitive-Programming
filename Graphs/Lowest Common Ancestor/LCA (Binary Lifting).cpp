// Time complexity: O(nlogn) build, O(logn) per query
// Problem link: https://cses.fi/problemset/task/1688

#include <bits/stdc++.h>
 
using namespace std;
 
#define ar array
#define ll long long
 
const int MAX_N = 2e5 + 1;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;
 
const int MAX_L = 20;
 
int n, q, par[MAX_N][MAX_L], dep[MAX_N];
vector<int> adj[MAX_N];
 
void dfs(int u, int p = 0) {
    par[u][0] = p;
    for (int i = 1; i < MAX_L; i++) 
        par[u][i] = par[par[u][i - 1]][i - 1];
    for (int v : adj[u]) {
        if (v == p) continue;
        dep[v] = dep[u] + 1;
        dfs(v, u);
    }
}
 
int ancestor(int u, int k) {
    for (int i = 0; i < MAX_L; i++) 
        if (k & (1 << i)) 
            u = par[u][i];
    return u;
}
 
int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    u = ancestor(u, dep[u] - dep[v]);
    if (u == v) return u;
    for (int i = MAX_L - 1; i >= 0; i--)
        if (par[u][i] != par[v][i])
            u = par[u][i], v = par[v][i];
    return par[u][0];
}
 
void solve() {
    cin >> n >> q;
    for (int v = 2; v <= n; v++) {
        int u; cin >> u;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1);
    while (q--) {
        int u, v; cin >> u >> v;
        cout << lca(u, v) << "\n";
    }
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