// Traveling Salesman Problem (A classic bitmask DP problem)
// Given a set of cities(nodes), find a minimum weight Hamiltonian Cycle/Tour
// Easier to solve using adjacent matrix
// Time complexity: (N^2 x 2^N)
// Reference: https://codingblocks.com/resources/travelling-salesman/

#include <bits/stdc++.h>

using namespace std;

const int INF = 1 << 30;
const int MAX_N = 10;
const int MAX_L = 20; // ~ Log N
const long long MOD = 1e9 + 7;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) (S & (-S))
#define isBitSet(S, i) ((S >> i) & 1)

int V, E, adj[MAX_N][MAX_N], dp[1 << MAX_N][MAX_N];

int tsp(int mask, int u) {
    if (mask == (1 << V) - 1) // base case, all nodes visited
        return adj[u][0];

    if(dp[mask][u] != -1)
	   return dp[mask][u];

    int ans = INF;
	// Visit all the unvisited nodes and take the best route
	for (int v = 0; v < V; v++) {
		if ((mask & (1 << v)) == 0) { // this node is unvisited
			int cur = adj[u][v] + tsp(mask | (1 << v), v);
			ans = min(ans, cur);
		}
	}

	return dp[mask][u] = ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    memset(adj, -1, sizeof adj);
	memset(dp, -1, sizeof dp);
	cin >> V >> E;
	for (int i = 0; i < V; i++) adj[i][i] = 0;
	for (int i = 0; i < E; i++) {
        int x, y, w; cin >> x >> y >> w;
        adj[x][y] = adj[y][x] = w;
	}
	cout << tsp(1, 0); // mask == 1 means all nodes are unvisited
}
