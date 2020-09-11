// Convert the Lowest Common Ancestor (LCA) problem into the Range Minimum Query (RMQ) Problem
// RMQ can be solved using Sparse Table
// Time complexity: O(nlogn) build, O(1) per query
// Problem link: https://cses.fi/problemset/task/1688

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 2e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

const int MAX_L = 30;

int n, q, idx;
int dep[2 * MAX_N], euler[2 * MAX_N], first[MAX_N], lg[2 * MAX_N];
ar<int,2> dp[2 * MAX_N][MAX_L]; // need to store both the indices and the min value
vector<int> adj[MAX_N];

void dfs(int u, int p = 0, int h = 0) {
    euler[++idx] = u;
    dep[idx] = h;
    first[u] = idx;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u, h + 1);
            euler[++idx] = u;
            dep[idx] = h;
        }
    }
}

void build_lg_table() {
    lg[1] = 0;
    for (int i = 2; i <= 2 * n; i++) 
        lg[i] = lg[i / 2] + 1;
}
 
void build_sparse_table() {
    for (int i = 1; i <= 2 * n; i++)
        dp[i][0] = {dep[i], euler[i]};
    for (int j = 1; j < MAX_L; j++)
        for (int i = 1; i + (1 << j) <= 2 * (n + 1); i++)
            dp[i][j] = min(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
}

int min_query(int l, int r) { 
    int k = lg[r - l + 1];
    return min(dp[l][k], dp[r - (1 << k) + 1][k])[1]; // return the index with min value
}

int lca(int u, int v) {
    int l = first[u], r = first[v];
    if (l > r) swap(l, r);
    return min_query(l, r);
}
 
void solve() {
    cin >> n >> q;
    for (int v = 2; v <= n; v++) {
        int u; cin >> u;
        adj[u].push_back(v);
    }
    dfs(1);
    build_lg_table();
    build_sparse_table();
    while (q--) {
        int a, b; cin >> a >> b;
        cout << lca(a, b) << "\n";
    }
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