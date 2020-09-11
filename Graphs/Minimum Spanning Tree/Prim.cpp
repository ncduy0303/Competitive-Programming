// Prim Agorithm is similar to Dijkstra
// Time Complexity: O(mlogn)
// Problem link: https://cses.fi/problemset/task/1675

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

int n, m, visited[MAX_N];
vector<ar<int,2>> adj[MAX_N];

void prim(int s = 1) {
    ll cost = 0;
    priority_queue<ar<ll,2>, vector<ar<ll,2>>, greater<ar<ll,2>>> pq;
    visited[s] = 1; 
    for (auto [u, d] : adj[s]) 
        if (!visited[u]) 
            pq.push({d, u});
    while (pq.size()) {
        auto [d, u] = pq.top(); pq.pop();
        if (!visited[u]) {
            cost += d;
            visited[u] = 1;
            for (auto [v, w] : adj[u]) 
                if (!visited[v]) 
                    pq.push({w, v});
        }
    } 
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            cout << "IMPOSSIBLE\n";
            exit(0);
        }
    }
    cout << cost << "\n";
}

void solve() {
    cin >> n >> m;    
    for(int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v, w}); 
        adj[v].push_back({u, w});
    }
    prim();
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