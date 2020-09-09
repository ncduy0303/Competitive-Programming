// Prim Algorithm for finding Maximum Spanning Tree (MST)
// Prim Agorithm has similar ideas to Dijkstra
// Time Complexity: O(ElogV)

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

int V, E, visited[MAX_N] = {0};
vector<pair<int, int> > adj[MAX_N];
priority_queue<ii, vii, greater<ii> > pq;

void process(int u) {
    visited[u] = 1;
    for(int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i].first, w = adj[u][i].second;
        if (!visited[v]) pq.push({w, v});
    }
}

int Prim(int s) { //return mst_cost
    int mst_cost = 0;
    process(s);
    while(!pq.empty()) {
        pair<int, int> next = pq.top(); pq.pop();
        int w = next.first, v = next.second;
        if (!visited[v]) {
            mst_cost += w;
            process(v);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    
    cin >> V >> E;    
    for(int i = 0; i < E; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v, w}); 
        adj[v].push_back({u, w});
    }
    
    cout << Prim(0);
}
