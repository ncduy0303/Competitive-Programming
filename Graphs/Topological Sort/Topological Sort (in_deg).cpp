// Greedily take all nodes with in_deg == 0 and push them into the topological ordering, then decrease the in_deg of other nodes accordingly
// Problem link: https://cses.fi/problemset/task/1679

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

int n, m, visited[MAX_N], in_deg[MAX_N];
vector<int> adj[MAX_N], topo;
 
void build_topo() {
    for (int u = 1; u <= n; u++) 
        for (int v : adj[u]) 
            in_deg[v]++;
    queue<int> q;
    for (int u = 1; u <= n; u++) 
        if (in_deg[u] == 0) 
            q.push(u);
    while (q.size()) {
        int u = q.front(); q.pop();
        topo.push_back(u);
        for (int v : adj[u]) {
            in_deg[v]--;
            if (in_deg[v] == 0) q.push(v);
        }
    }
    // detect cycle
    for (int i = 1; i <= n; i++) { 
        if (in_deg[i]) {
            cout << "IMPOSSIBLE\n";
            exit(0);
        }
    }
}

void solve() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
    }
    build_topo();
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