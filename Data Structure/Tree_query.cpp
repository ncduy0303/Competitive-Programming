// Query on tree
// Problem: https://cses.fi/problemset/task/1137/

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 5;
const int MAX_L = 20;
const int MOD = 1e9 + 7;
const int INF = 1e9 + 7;

typedef long long ll;
typedef vector<int> vi;

int n, q, arr[MAX_N], id[MAX_N], num_child[MAX_N];
ll ft[MAX_N];
vi adj[MAX_N], topo;

void update (int x, int v) {
    for (; x <= n; x += x&-x)
        ft[x] += v;
}

ll sum(int x) {
    ll res = 0;
    for (; x; x -= x&-x)
        res += ft[x];
    return res;
}

ll rsq(int x, int y) {
    return sum(y) - sum(x - 1);
}

void dfs(int u = 1, int p = 1) {
    topo.push_back(u);
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
            num_child[u] += num_child[v] + 1;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> arr[i];
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs();
    for (int i = 1; i <= n; i++) {
        id[topo[i - 1]] = i;
        update(i, arr[topo[i - 1]]);
    }
    while (q--) {
        int c; cin >> c;
        if (c == 1) {
            int u, x; cin >> u >> x;
            update(id[u], x - arr[u]);
            arr[u] = x;
        }
        else {
            int u; cin >> u;
            cout << rsq(id[u], id[u] + num_child[u]) << "\n";
        }
    }
}
