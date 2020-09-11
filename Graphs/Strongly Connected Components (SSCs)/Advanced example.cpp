// Create a new graph by merging all nodes in a SCC into a single node, then DP
// Problem link: https://cses.fi/problemset/task/1686/

#include <bits/stdc++.h>
 
using namespace std;
 
#define ar array
#define ll long long
 
const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;
 
int n, m, scc, arr[MAX_N], comp[MAX_N], visited[MAX_N];
ll new_arr[MAX_N], dp[MAX_N];
vector<int> adj[2][MAX_N], new_adj[MAX_N], dfn;
 
void dfs(int u, int t) {
    visited[u] = 1;
    if (t == 1) {
        comp[u] = scc;
        new_arr[scc] += arr[u];
    }
    for (int v : adj[t][u]) {
        if (!visited[v]) {
            dfs(v, t);
        }
    }
    if (t == 0) dfn.push_back(u);
}
 
void kosaraju() {
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(i, 0);
        }
    }
    memset(visited, 0, sizeof visited);
    for (int i = n - 1; i >= 0; i--) {
        if (!visited[dfn[i]]) {
            scc++;
            dfs(dfn[i], 1);
        }
    }
}
 
ll dfs2(int u) {
    ll res = 0;
    for (int v : new_adj[u]) {
        if (!dp[v]) dfs2(v);
        res = max(res, dp[v]);
    }
    return dp[u] = res + new_arr[u];
}
 
void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> arr[i];
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[0][u].push_back(v);
        adj[1][v].push_back(u);
    }
    kosaraju();
    // merging nodes in a SCC
    for (int u = 1; u <= n; u++) 
        for (int v : adj[0][u])
            if (comp[u] != comp[v])
                new_adj[comp[u]].push_back(comp[v]);
    // DP on the new graph
    ll ans = 0;
    for (int i = 1; i <= scc; i++)
        ans = max(ans, dfs2(i));
    cout << ans << "\n";
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