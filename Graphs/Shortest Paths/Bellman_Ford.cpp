// Time complexity: O(nm)
// Problem link: https://cses.fi/problemset/task/1197/

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 2.5e3 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e15;

int n, m, par[MAX_N];
vector<ar<ll,2>> adj[MAX_N];
vector<ll> dist;

void bellman_ford(int s) {
    dist.assign(n + 1, LINF);
    dist[s] = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int u = 1; u <= n; u++) {
            for (auto [v, w] : adj[u]) {
                if (dist[u] + w < dist[v]) {
                    par[v] = u;
                    dist[v] = dist[u] + w;
                }
            }
        }
    }
}

void cycle_detect() {
    int cycle = 0;
    for (int u = 1; u <= n; u++) {
        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                cycle = v; 
                break;
            }
        }
    }
    if (!cycle) cout << "NO\n";
    else {
        cout << "YES\n";
        // backtrack to print the cycle
        for (int i = 0; i < n; i++) cycle = par[cycle];
        vector<int> ans; ans.push_back(cycle);
        for (int i = par[cycle]; i != cycle; i = par[i]) ans.push_back(i); 
        ans.push_back(cycle);
        reverse(ans.begin(), ans.end());
        for (int x : ans) cout << x << " ";
        cout << "\n";
    }
}
 
void solve() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }
    bellman_ford(1);
    cycle_detect();
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