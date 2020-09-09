// Problem link: https://cses.fi/problemset/task/1668

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

int n, m, color[MAX_N];
vector<int> adj[MAX_N];

void bfs(int s) {
    queue<int> q;
    color[s] = 1; q.push(s);
    while (q.size()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (!color[v]) {
                color[v] = color[u] % 2 + 1;
                q.push(v);
            }
            else if (color[v] == color[u]) {
                cout << "IMPOSSIBLE\n";
                exit(0);
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
    for (int i = 1; i <= n; i++)
        if (!color[i])
            bfs(i);
    for (int i = 1; i <= n; i++) 
        cout << color[i] << " ";
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