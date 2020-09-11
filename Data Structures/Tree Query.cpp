// Query on tree using eulerian ordering and fenwick tree
// Problem link: https://cses.fi/problemset/task/1137/

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 2e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

#define LSOne(S) ((S) & (-S))

int n, q, arr[MAX_N], tin[MAX_N], tout[MAX_N], timer;
ll ft[2 * MAX_N];
vector<int> adj[MAX_N];
 
void update(int x, int v) {
    for (; x <= 2 * n; x += LSOne(x))
        ft[x] += v;
}
 
ll sum(int x) {
    ll res = 0;
    for (; x; x -= LSOne(x))
        res += ft[x];
    return res;
}
 
ll rsq(int a, int b) {
    return sum(b) - sum(a - 1);
}
 
void dfs(int u, int p = 0) {
    tin[u] = ++timer;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
        }
    }
    tout[u] = ++timer;
}
 
void solve() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> arr[i];
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1);
    for (int i = 1; i <= n; i++) {
        update(tin[i], arr[i]);
        update(tout[i], arr[i]);
    }
    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int s, x; cin >> s >> x;
            update(tin[s], x - arr[s]);
            update(tout[s], x - arr[s]);
            arr[s] = x;
        }
        else {
            int s; cin >> s;
            cout << rsq(tin[s], tout[s]) / 2 << "\n";
        }
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