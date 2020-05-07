// Idea: notice that traversal path of a typical DFS is a reverse topological order

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

int V, E, visited[MAX_N];
vector<int> adj[MAX_N];
vector<int> topo;
//For a rooted tree, an array par[MAX_N] storing nodes' direct ancestors can be used instead of adjacent list adj

void dfs(int u) { //applying DFS for topoligical sort
    visited[u] = 1; //visited
    for(int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];
        if (!visited[v]) 
            dfs(v);
    }
    topo.push_back(u);
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
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }
    reverse(topo.begin(), topo.end());
    for(int i = 0; i < topo.size(); i++)
        cout << topo[i] << " ";
}
