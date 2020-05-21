// Given an undirected graph, find all bridges and articulation points
// Idea: perform a DFS to form a DFS spanning tree, an edge u-v is a bridge if and only if there is a back edge connecting a descendant of v and an ancestor of u
// This is an important to concept in Tarjan's algorithm to find strongly connected components
// Time complexity: O(V + E)

// There is a great tutorial on Codeforces about this topic: https://codeforces.com/blog/entry/68138

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
// then dfs_low[u] can only be made smaller if there is a back edge to form a cycle and v is currently visited

int V, E, dfsCounter = 0;
int dfs_num[MAX_N], dfs_low[MAX_N], visited[MAX_N];
vector<int> adj[MAX_N];

void dfs(int u, int p = -1) {
    dfs_num[u] = dfs_low[u] = dfsCounter++;
    visited[u] = 1;
    int num_child = 0;
    for (int v : adj[u]) {
        if (v == p) continue; //ignore the case when a child is connected to its parent
        if (visited[v]) // back edge
            dfs_low[u] = min(dfs_low[u], dfs_num[v]); // update
        else { // tree edge
            dfs(v, u);
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);  // subtree, always update
            num_child++;
            if (dfs_low[v] > dfs_num[u]) // bridge
                cout << "Edge " << u << "-" << v << " is a bridge\n";

            if (dfs_low[v] >= dfs_num[u] && p != -1) // articulation point, the root node need to be treated separately
                cout << "Node " << u << " is an articulation point\n";
        }
    }
    if (p == -1 && num_child > 1) // check whether the root node is an articulation point if has more than 1 child
        cout << "Node " << u << " is an articulation point\n";
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
        adj[y].push_back(x);
    }
    memset(dfs_low, -1, sizeof dfs_low);
    memset(dfs_num, -1, sizeof dfs_num);
    memset(visited, 0, sizeof visited);
    for (int i = 1; i <= V; i++)
        if (!visited[i])
            dfs(i);
}

/* Example input:
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
