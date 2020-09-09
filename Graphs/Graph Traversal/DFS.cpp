#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

int n, m, visited[MAX_N], num;
vector<int> adj[MAX_N];

void dfs(int u) {
    visited[u] = 1;
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(v);
        }
    }
}

void solve() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(i);
            num++;
        }
    }
    cout << num << "\n"; // number of connected components

    /*
    Example input:
        6 4
        1 2
        5 1
        2 4
        4 6
    Expected output:
        2
    */
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