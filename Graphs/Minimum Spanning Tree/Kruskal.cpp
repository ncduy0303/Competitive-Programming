// Need to use edge list for Kruskal
// Time Complexity: O(mlogn)
// Problem link: https://cses.fi/problemset/task/1675

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

int n, m, par[MAX_N];
vector<array<int,3>> edges;
 
int find(int u) {
    return u == par[u] ? u : par[u] = find(par[u]);
}
 
void unite(int u, int v) {
    par[find(u)] = find(v);
}

void kruskal() {
    sort(edges.begin(), edges.end());
    for (int i = 1; i <= n; i++) par[i] = i;

    ll cnt = 0, cost = 0;
    for (auto [w, u, v] : edges) {
        u = find(u), v = find(v);
        if (u != v) {
            par[u] = v;
            cost += w;
            cnt++;
        }
    }
    if (cnt == n - 1) cout << cost << "\n";
    else cout << "IMPOSSIBLE\n";
}

void solve() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        edges.push_back({w, u, v});
    }
    kruskal();
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