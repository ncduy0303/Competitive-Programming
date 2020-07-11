/* NOI 2017 - Hotspot
Idea: given A and B, use Dijkstra (BFS for non-weighted graph) to find all shortest path from A and from B
Notice that a node u exists on the shortest path from A to B <=> dist[A][B] == dist[A][u] + dist[B][u]
=> Calculate all the probabilities for all u and return the maximum one

Time Complexity: O(K(N + M))
*/

#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;
const int MAX_N = 5000 + 5;
const int MAX_L = 20; // ~ Log N
const long long MOD = 1e9 + 7;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) (S & (-S))
#define isBitSet(S, i) ((S >> i) & 1)

int V, E, K;
int dist[MAX_N][MAX_N], ways[MAX_N][MAX_N];
vector<int> adj[MAX_N];
double chance[MAX_N];

void bfs(int s) {
	queue<pair<int, int>> q;
	q.push({0, s});
	dist[s][s] = 0; ways[s][s] = 1;
	while (!q.empty()){
		int d = q.front().first, u = q.front().second;
		q.pop();
		if (dist[s][u] < d) continue;
		for (int v: adj[u]) {
			if (dist[s][u] + 1 < dist[s][v]) { // Shorter path found
				dist[s][v] = dist[s][u] + 1;
				q.push({dist[s][v], v});
				ways[s][v] = ways[s][u];
			}
			else if (dist[s][u] + 1 == dist[s][v]) ways[s][v] += ways[s][u];
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
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    fill_n(&dist[0][0], MAX_N * MAX_N, INF);
    for (int i = 0; i < V; i++) {
		chance[i] = 0.0000;
		bfs(i);
	}
    cin >> K;
    while (K--) {
        int a, b; cin >> a >> b;
		for (int i = 0; i < V; i++) {
			if (dist[a][i] + dist[i][b] == dist[a][b]) { // Shortest path through node i
				double tmp = (double)ways[a][i] * (double)ways[i][b];
				chance[i] += tmp / (double)ways[a][b];
			}
		}
    }
    double maxchance = 0.0000;
	int node = 0;
	for (int i = 0; i < V; i++) {
		if (chance[i] > maxchance){
			maxchance = chance[i];
			node = i;
		}
	}
	cout << node;
}
