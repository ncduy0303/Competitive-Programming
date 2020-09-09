// Find all pair shortest paths
// Time complexity: O(n^3)
// Problem link: https://cses.fi/problemset/task/1672

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 500 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e15;

int n, m, q;
ll dist[MAX_N][MAX_N];

void floyd_warshall() { // 4 lines
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++) 
            for (int j = 1; j <= n; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}
 
void solve() {
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            dist[i][j] = (i == j) ? 0 : LINF;
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        dist[u][v] = dist[v][u] = min(dist[u][v], (ll)w); 
    }
    floyd_warshall();
    while (q--) {
        int u, v; cin >> u >> v;
        cout << (dist[u][v] < LINF ? dist[u][v] : -1) << "\n";
    }
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