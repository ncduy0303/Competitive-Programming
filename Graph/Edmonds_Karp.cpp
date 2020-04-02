// Maximum Flow (Edmonds-Karp Algorithm)
// Given a directed network G with edge capacity c: (u, v), find the maximum flow from a source s to a tank t
// Idea: finding augmenting paths from s to t using BFS
// Time complexity: O(VE^2) in total, O(VE) BFS iterations with O(E) per BFS
// Reference: https://github.com/mochow13/competitive-programming-library/blob/master/Graph/Max%20Flow%20Edmond%20Karp.cpp

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

struct max_flow_graph {
	int V;
	struct edge {
		int src, dst, cap, res;
		size_t rev;
	};
	edge &rev(edge e) { return adj[e.dst][e.rev]; };

	vector<vector<edge>> adj;
	max_flow_graph(int V) : V(V), adj(V) { }
	void add_edge(int src, int dst, int cap) {
		adj[src].push_back({src, dst, cap, 0, adj[dst].size()});   // original edge
		adj[dst].push_back({dst, src, 0, 0, adj[src].size() - 1}); // residual back edge (notice cap = 0)
	}
	int max_flow(int s, int t) {
		for (int u = 0; u < V; u++)
			for (auto &e : adj[u])
                e.res = e.cap;
		int total = 0;
		while (true) {
			vector<int> prev(V, -1); prev[s] = -2;
			queue<int> q; q.push(s);
			while (!q.empty() && prev[t] == -1) {
				int u = q.front(); q.pop();
				for (edge &e : adj[u]) {
					if (prev[e.dst] == -1 && e.res > 0) {
						prev[e.dst] = e.rev;
						q.push(e.dst);
					}
				}
			}
			if (prev[t] == -1) break;
			int inc = INF;
			for (int u = t; u != s; u = adj[u][prev[u]].dst)
				inc = min(inc, rev(adj[u][prev[u]]).res);
			for (int u = t; u != s; u = adj[u][prev[u]].dst) {
				adj[u][prev[u]].res += inc;
				rev(adj[u][prev[u]]).res -= inc;
			}
			total += inc;
		}
		return total;
	}
};

int V, E, s, t;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> V >> E >> s >> t;
    max_flow_graph adj(V);
    for (int i = 0; i < E; i++) {
        int x, y, w; cin >> x >> y >> w;
        adj.add_edge(x, y, w);
    }
    cout << adj.max_flow(s, t);
}

/*
Example input:
5 7 0 1
0 2 100
0 3 50
2 3 50
3 4 100
2 4 50
2 1 50
4 1 125

Expected output: 150
*/
