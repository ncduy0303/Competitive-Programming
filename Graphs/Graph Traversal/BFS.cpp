#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

int n, m;
vector<int> adj[MAX_N], dist;

void bfs(int s) {
    dist.assign(n + 1, -1);
    queue<int> q;
    dist[s] = 0; q.push(s);
    while (q.size()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
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
    bfs(1);
    for (int i = 1; i <= n; i++) 
        cout << dist[i] << " ";
    cout << "\n";

    /*
    Example input:
        6 4
        1 2
        5 1
        2 4
        4 6
    Expected output:
        0 1 -1 2 1 3
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