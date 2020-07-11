// 0-1 BFS for SSSP
// Idea: same as normal BFS, but now when processing neighbours of a node, there are 2 cases:
// 1) Push the node to the front of the queue (To push a node with same level - 0 edge)
// 2) Push the node to the back of the queue (To push a node on next level - 1 edge)

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

int V, E, dist[MAX_N]; 
//dist[u] = -1 if u is unvisited, = 0 for source, shortes distance from source if > 0 (only applicable for unweighted graph)
deque<int> Q;
vector<pair<int, int>> adj[MAX_N];
//For a rooted tree, an array par[MAX_N] storing nodes' direct ancestors can be used instead of adjacent list adj

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
  
    cin >> V >> E;
    for (int i = 0; i < E; i++) {
        int x, y, w; cin >> x >> y >> w; // w here is either 0 or 1 only
        adj[x].push_back({y, w});
        adj[y].push_back({x, w});
    }
    
    memset(dist, -1, sizeof dist);
    Q.push_front(0); dist[0] = 0;
    while (!Q.empty()) {
        int u = Q.front(); Q.pop_front();
        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i].first, w = adj[u][i].second;
            if (dist[v] == -1) {
                dist[v] = dist[u] + w;
                if (w == 1) Q.push_back(v);
                else Q.push_front(v);
            }
        }
    }
}
