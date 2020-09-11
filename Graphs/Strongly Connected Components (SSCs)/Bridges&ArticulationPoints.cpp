// Given an undirected graph, find all bridges and articulation points
// Perform a DFS to form a DFS spanning tree
// u-v is a bridge <=> there is a back edge connecting a descendant of v and an ancestor of u
// Time complexity: O(n + m)

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
// dfs_low[u] can only be made smaller if there is a back edge to form a cycle and v is currently visited

int n, m, dfsCounter;
int dfs_num[MAX_N], dfs_low[MAX_N], visited[MAX_N];
vector<int> adj[MAX_N];

void dfs(int u, int p = -1) {
    dfs_num[u] = dfs_low[u] = dfsCounter++;
    visited[u] = 1;
    int num_child = 0;
    for (int v : adj[u]) {
        if (v == p) continue; 
        // back edge
        if (visited[v]) dfs_low[u] = min(dfs_low[u], dfs_num[v]); 
        // tree edge
        else { 
            dfs(v, u);
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);  
            num_child++;
            if (dfs_low[v] > dfs_num[u]) 
                cout << "Edge " << u << "-" << v << " is a bridge\n";
            if (dfs_low[v] >= dfs_num[u] && p != -1)
                cout << "Node " << u << " is an articulation point\n";
        }
    }
    // special case: the root node is an articulation point if it has more than 1 child
    if (p == -1 && num_child > 1) 
        cout << "Node " << u << " is an articulation point\n";
}

void solve() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    memset(dfs_low, -1, sizeof dfs_low);
    memset(dfs_num, -1, sizeof dfs_num);
    for (int i = 1; i <= n; i++)
        if (!visited[i])
            dfs(i);

    /* 
    Example input:
        12 16
        1 3
        3 5
        5 7
        3 7
        3 8
        1 5
        1 6
        3 6
        6 2
        2 8
        2 4
        4 10
        1 9
        9 11
        11 12
        9 12
        
    Expected output:
        Edge 4-10 is a bridge
        Node 4 is an articulation point
        Edge 2-4 is a bridge
        Node 2 is an articulation point
        Node 9 is an articulation point
        Edge 1-9 is a bridge
        Node 1 is an articulation point
    */
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