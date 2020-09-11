// Union-Find Disjoint Set
// Union by rank & Path compression

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

int n, par[MAX_N], sz[MAX_N], num_grp;
 
int find(int u) {
    return u == par[u] ? u : par[u] = find(par[u]);
}
 
void unite(int u, int v) {
    // par[find(u)] = find(v);
    u = find(u), v = find(v);
    num_grp -= (u == v);
    if (sz[u] > sz[v]) {
        par[v] = u;
        sz[u] += sz[v];
    } else {
        par[u] = v;
        sz[v] += sz[u];
    }
}

void solve() {
    cin >> n;
    num_grp = n;
    for (int i = 1; i <= n; i++) par[i] = i, sz[i] = 1;
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