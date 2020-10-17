// 2-SAT Problem
// Time complexity: O(n + m), using Kosaraju to find SCCs
// Problem link: https://cses.fi/problemset/task/1684/

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

int n, m, scc, visited[2 * MAX_N], comp[2 * MAX_N];
char ans[MAX_N];
vector<int> adj[2][2 * MAX_N], dfn;
// adj[0] is the original graph, adj[1] is the transposed graph

// t = 0 means 1st pass, t = 1 means 2nd pass
void dfs(int u, int t) {
    visited[u] = 1;
    if (t == 1) comp[u] = scc;
    for (int v : adj[t][u]) {
        if (!visited[v]) {
            dfs(v, t);
        }
    }
    if (t == 0) dfn.push_back(u);
}

void kosaraju() {
    for (int i = 1; i <= 2 * n; i++) {
        if (!visited[i]) {
            dfs(i, 0);
        }
    }
    memset(visited, 0, sizeof visited);
    for (int i = 2 * n; i > 0; i--) {
        if (!visited[dfn[i]]) {
            scc++;
            dfs(dfn[i], 1);
        }
    }
}

void solve() {
    cin >> m >> n;
    for (int i = 0; i < m; i++) {
        int u1, u2; char c1, c2; cin >> c1 >> u1 >> c2 >> u2;
        u1 *= 2; u2 *= 2; 
        if (c1 == '-') u1 ^= 1;
        if (c2 == '-') u2 ^= 1;
        adj[0][u1 ^ 1].push_back(u2);
        adj[0][u2 ^ 1].push_back(u1);
    }
    for (int i = 1; i <= 2 * n; i++) {
        for (int j : adj[0][i]) {
            adj[1][j].push_back(i);
        }
    }
    kosaraju();
    for (int i = 1; i <= n; i++) {
        if (comp[2 * i] == comp[2 * i + 1]) { 
            cout << "IMPOSSIBLE\n";
            return;
        }
        ans[i] = (comp[2 * i] > comp[2 * i + 1]) ? '+' : '-';
    }
    for (int i = 1; i <= n; i++) cout << ans[i] << " ";
    cout << "\n";
}
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
 
    int tc; tc = 1;
    for (int t = 1; t <= tc; t++) {
        //cout << "Case #" << t  << ": ";
        solve();
    }
}