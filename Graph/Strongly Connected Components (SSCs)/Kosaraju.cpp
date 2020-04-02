// Kosaraju's algorithm to find strongly connected components (SCCs)
// Idea: Running DFS twice
// 1st pass done on the original graph and record the topological order of the nodes
// 2nd pass done on the transposed graph using the order found in the 1st pass
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

int V, E, numSCC = 0, visited[MAX_N];
vector<int> adj[MAX_N], adj_T[MAX_N], S;

void Kosaraju(int u, int pass) {
    visited[u] = 1;
    if (pass == 1) { // 1st pass
        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];
            if (!visited[v]) Kosaraju(v, 1); // first time visited
        }
        S.push_back(u);
    }
    else { // 2nd pass
        cout << u << " ";
        for (int i = 0; i < adj_T[u].size(); i++) {
            int v = adj_T[u][i];
            if (!visited[v]) Kosaraju(v, 2); // first time visited
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
        adj_T[y].push_back(x);
    }

    memset(visited, 0, sizeof visited);
    for (int i = 0; i < V; i++)
        if (!visited[i])
            Kosaraju(i, 1);

    memset(visited, 0, sizeof visited);
    for (int i = V - 1; i >= 0; i--) {
        if (!visited[S[i]]) {
            cout << "SCC " << ++numSCC << ": ";
            Kosaraju(S[i], 2);
            cout << "\n";
        }
    }
}
