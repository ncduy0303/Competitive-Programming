// Traversal path of a typical DFS is a reverse topological order
// Problem link: https://cses.fi/problemset/task/1679

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

int n, m, visited[MAX_N];
vector<int> adj[MAX_N], topo;
 
void dfs(int u) {
    visited[u] = 1;
    for (int v : adj[u]) {
        if (!visited[v]) dfs(v);
        else if (visited[v] == 1) {
            cout << "IMPOSSIBLE\n";
            exit(0);
        }
    }
    visited[u] = 2;
    topo.push_back(u);
}
 
void solve() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
    }
    for (int i = 1; i <= n; i++)
        if (!visited[i])
            dfs(i);
    reverse(topo.begin(), topo.end());
    for (int x : topo) cout << x << " ";
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