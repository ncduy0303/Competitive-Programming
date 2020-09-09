// 0-1 BFS for SSSP
// Idea: same as normal BFS, but now when processing neighbours of a node, there are 2 cases:
// 1) Push the node to the front of the queue (To push a node with same level - 0 edge)
// 2) Push the node to the back of the queue (To push a node on next level - 1 edge)

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

int n, m;
vector<ar<int,2>> adj[MAX_N];
vector<int> dist;

void bfs(int s) {
    dist.assign(n + 1, -1);
    deque<int> q;
    dist[s] = 0; q.push_front(s);
    while (q.size()) {
        int u = q.front(); q.pop_front();
        for (auto [v, w] : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + w;
                if (w == 1) q.push_back(v);
                else q.push_front(v);
            }
        }
    }
}

void solve() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w; // w is 0 or 1
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    bfs(1);
    for (int i = 1; i <= n; i++) 
        cout << dist[i] << " ";
    cout << "\n";

    /*
    Example input:
        6 5
        1 2 0 
        5 1 1
        2 4 1
        4 6 1
        1 4 0
    Expected output:
        0 0 -1 0 1 1
    */
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int tc; tc = 1;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t  << ": ";
        solve();
    }
}