/* NOI 2013: Ferries
Idea: Modified Dijkstra (on reverse graph)
Time Complexity: O(V + ElogV)
*/

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
priority_queue<int> C[MAX_N];

void Dijkstra(int s) {
    dist.assign(V + 1, INF);
    dist[s] = 0;
    priority_queue<ii, vii, greater<ii> > pq;
    pq.push({0, s});
    while(!pq.empty()) {
        pair<int, int> next = pq.top(); pq.pop();
        int d = next.first, u = next.second;
        if (d > dist[u]) continue;
        for(int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i].first;

            int w = C[v].top(); C[v].pop();

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
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
    for(int i = 0; i < E; i++) {
        int x, y, w; cin >> x >> y >> w;
        adj[y].push_back({x, w});
        C[x].push(w);
    }
    Dijkstra(V);
    cout << dist[1];
}
