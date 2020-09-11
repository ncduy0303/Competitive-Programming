// Time complexity: O(nlogn) build, O(logn) per query
// Problem link: https://cses.fi/problemset/task/1688

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 2e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

const int MAX_L = 18;

int n, q, dp[MAX_N][MAX_L], dep[MAX_N];
vector<int> adj[MAX_N];
 
void dfs(int u, int p = 0) {
    dp[u][0] = p;
    dep[u] = dep[p] + 1;
    for (int i = 1; i < MAX_L; i++)
        dp[u][i] = dp[dp[u][i - 1]][i - 1];
    for (int v : adj[u]) 
        if (v != p) 
            dfs(v, u);
}
 
int ancestor(int u, int k) {
    for (int i = 0; i < MAX_L && u; i++)
        if (k & (1 << i))
            u = dp[u][i];
    return u;
}
 
int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    u = ancestor(u, dep[u] - dep[v]);
    if (u == v) return u;
    for (int i = MAX_L - 1; i >= 0; i--)
        if (dp[u][i] != dp[v][i])
            u = dp[u][i], v = dp[v][i];
    return dp[u][0];
}
 
void solve() {
    cin >> n >> q;
    for (int v = 2; v <= n; v++) {
        int u; cin >> u;
        adj[u].push_back(v);
    }
    dfs(1);
    while (q--) {
        int a, b; cin >> a >> b;
        cout << lca(a, b) << "\n";
    }
    cout << "\n";
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