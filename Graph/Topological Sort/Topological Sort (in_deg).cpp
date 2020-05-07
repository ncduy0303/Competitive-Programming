// Idea: greedily take all nodes with in_deg == 0 and push them into the topological ordering, then decrease the in_deg of other nodes accordingly

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

void build_topo() {
	int in_deg[V + 1] = {0};
	for (int u = 1; u <= V; u++) {
        for (int v : adj[u]) {
            in_deg[v]++;
        }
	}
	queue<int> q;
	for (int u = 1; u <= V; u++) {
        if (in_deg[u] == 0) {
            q.push(u);
        }
	}
	while (!q.empty()) {
		int u = q.front(); q.pop();
		topo.push_back(u);
		for (int v : adj[u]) {
            in_deg[v]--;
            if (in_deg[v] == 0) {
                q.push(v);
            }
		}
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
    build_topo();
    for(int i = 0; i < topo.size(); i++)
        cout << topo[i] << " ";
}
