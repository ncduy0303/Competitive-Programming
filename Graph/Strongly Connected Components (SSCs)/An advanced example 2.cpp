// Problem: https://cses.fi/problemset/task/1686/

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 5;
const int MAX_L = 20;
const int MOD = 1e9 + 7;
const long long INF = 1e18 + 7;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;

int V, E, numSCC = 0;
int arr[MAX_N], comp[MAX_N], visited[MAX_N];
ll new_arr[MAX_N];
vi adj[MAX_N], adj_T[MAX_N], SCC[MAX_N], topo;

void dfs(int u, int pass) { // Kosaraju
    visited[u] = 1;
    if (pass == 1) {
        for (int v : adj[u])
            if (!visited[v])
                dfs(v, pass);
        topo.push_back(u);
    }
    else {
        comp[u] = numSCC;
        new_arr[numSCC] += arr[u];
        for (int v : adj_T[u])
            if (!visited[v])
                dfs(v, pass);
    }
}

ll dp[MAX_N]; // dp[i] is the maximum number can be collected if start at the i-th SCC component
ll memo(int u) { // DP on DAG
    if (dp[u]) return dp[u];
    ll res = 0;
    for (int v : SCC[u])
        res = max(res, memo(v));
    return dp[u] = res + new_arr[u];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> V >> E;
    for (int i = 1; i <= V; i++) cin >> arr[i];
    for (int i = 1; i <= E; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj_T[v].push_back(u);
    }
    memset(visited, 0, sizeof visited);
    for (int i = 1; i <= V; i++)
        if (!visited[i])
            dfs(i, 1);
    memset(visited, 0, sizeof visited);
    for (int i = V - 1; i >= 0; i--)
        if (!visited[topo[i]])
            numSCC++, dfs(topo[i], 2);

    // Merging all nodes in each SCC into one single node => The new graph becomes a DAG
    for (int u = 1; u <= V; u++)
        for (int v : adj[u])
            if (comp[u] != comp[v])
                SCC[comp[u]].push_back(comp[v]);

    ll ans = 0;
    for (int i = 1; i <= numSCC; i++)
        ans = max(ans, memo(i));
    cout << ans;
}
