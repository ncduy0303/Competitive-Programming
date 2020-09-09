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

int V, E;
vector<pair<int, int> > adj[MAX_N];
vector<int> dist;

//Bellman_Ford O(VE)
void Bellman_Ford(int s) {
    dist.assign(V, INF);
    dist[s] = 0;
    for (int i = 0; i < V - 1; i++) {
        for (int u = 0; u < V; u++) {
            for (auto next : adj[u]) {
                int v = next.first, w = next.second;
                dist[v] = min(dist[v], dist[u] + w);
            }
        }
    }
}

//Detecting cycle
bool hasNegativeCycle() {
    bool ans = false;
    for (int u = 0; u < V; u++) {
        for (auto next : adj[u]) {
            int v = next.first, w = next.second;
            if (dist[v] > dist[u] + w) ans = true;
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> V >> E;
    for(int i = 0; i < E; i++) {
        int x, y, w; cin >> x >> y >> w;
        adj[x].push_back({y, w});
    }
    Bellman_Ford(0);
    bool has_cycle = hasNegativeCycle();
}
