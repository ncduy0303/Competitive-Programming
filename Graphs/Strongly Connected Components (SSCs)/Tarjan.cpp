// Tarjan's algorithm to find strongly connected components (SCCs)
// SSCs form subtrees in the DFS spanning tree
// Time complexity: O(n + m)
// Problem link: https://cses.fi/problemset/task/1682/

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

// dfs_num[u] stores the iteration counter when DFS visits node u for the 1st time
// dfs_low[u] stores the lowest dfs_num reachable from the current DFS spanning subtree of node u
// so dfs_num[u] == dfs_low[u] => u is a root of a SCC
// then dfs_low[u] can only be made smaller if there is a back edge to form a cycle and v is currently visited
// if we are at node u with node v as its neighbour and dfs_low[v] >= dfs_num[u], then u is an articulation point and edge u-v is a bridge

int n, m, scc, dfsCounter;
int dfs_num[MAX_N], dfs_low[MAX_N], visited[MAX_N];
stack<int> st;
vector<int> adj[MAX_N], comp[MAX_N];

// Modified DFS
void tarjan(int u) { 
    dfs_low[u] = dfs_num[u] = dfsCounter++;
    visited[u] = 1;
    st.push(u);
    for (int v : adj[u]) {
        if (dfs_num[v] == -1) tarjan(v); 
        if (visited[v]) dfs_low[u] = min(dfs_low[u], dfs_low[v]); 
    }

    if (dfs_low[u] == dfs_num[u]) {
        scc++;
        while (st.size()) {
            int v = st.top(); st.pop();
            visited[v] = 0;
            comp[scc].push_back(v);
            if (v == u) break;
        }
    }
}

void dfs(int u) {
    visited[u] = 1;
    for (int v : adj[u])
        if (!visited[v])
            dfs(v);
}

void solve() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
    }
    memset(dfs_low, -1, sizeof dfs_low);
    memset(dfs_num, -1, sizeof dfs_num);
    for (int i = 1; i <= n; i++)
        if (dfs_num[i] == -1)
            tarjan(i);

    if (scc == 1) cout << "YES\n";
    else {
        cout << "NO\n";
        memset(visited, 0, sizeof visited);
        dfs(comp[1][0]);
        if (!visited[comp[2][0]]) 
            cout << comp[1][0] << " " << comp[2][0] << "\n";
        else 
            cout << comp[2][0] << " " << comp[1][0] << "\n";
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