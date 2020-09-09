// Tarjan's algorithm to find strongly connected components (SCCs)
// Idea: SSCs form subtrees in the DFS spanning tree
// Time complexity: O(V + E)

#include <bits/stdc++.h>

using namespace std;

const int INF = 1 << 30;
const int MAX_N = 100000 + 5;
const int MAX_L = 20; // ~ Log N
const long long MOD = 1e9 + 7;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) (S & (-S))
#define isBitSet(S, i) ((S >> i) & 1)

// dfs_num[u] stores the iteration counter when DFS visits node u for the 1st time
// dfs_low[u] stores the lowest dfs_num reachable from the current DFS spanning subtree of node u
// so dfs_num[u] == dfs_low[u] => u is a root of a SCC
// then dfs_low[u] can only be made smaller if there is a back edge to form a cycle and v is currently visited
// if we are at node u with node v as its neighbour and dfs_low[v] >= dfs_num[u], then u is an articulation point and edge u-v is a bridge

int V, E, numSCC = 0, dfsCounter = 0;
int dfs_num[MAX_N], dfs_low[MAX_N], visited[MAX_N];
stack<int> S;
vector<int> adj[MAX_N];

void tarjanSCC(int u) { // Modified DFS
    dfs_low[u] = dfs_num[u] = dfsCounter++;
    visited[u] = 1;
    S.push(u);

    for (int v : adj[u]) {
        if (dfs_num[v] == -1) tarjanSCC(v); // first time visited
        if (visited[v]) dfs_low[u] = min(dfs_low[u], dfs_low[v]); // back edge
    }

    if (dfs_low[u] == dfs_num[u]) {
        cout << "SCC " << numSCC++ << ": ";
        while(!S.empty()) {
            int v = S.top(); S.pop();
            visited[v] = 0;
            cout << v << " ";
            if (v == u) break;
        }
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> V >> E;
    for (int i = 0; i < E; i++) {
        int x, y; cin >> x >> y;
        adj[x].push_back(y);
    }
    memset(dfs_low, -1, sizeof dfs_low);
    memset(dfs_num, -1, sizeof dfs_num);
    memset(visited, 0, sizeof visited);
    for (int i = 0; i < V; i++)
        if (dfs_num[i] == -1)
            tarjanSCC(i);
}
