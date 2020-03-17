/* NOI 2014 - Sightseeing
Idea: Maximum Spanning Tree + Dijkstra on the MST
Time Complexity: O(V + ElogV)
*/

#include <bits/stdc++.h>

using namespace std;

const int INF = 1 << 30;
const int MAX_N = 500000 + 5;
const int MAX_L = 20; // ~ Log N
const long long MOD = 1e9 + 7;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) (S & (-S))
#define isBitSet(S, i) ((S >> i) & 1)

int V, E, Q, par[MAX_N], dist[MAX_N] = {0};
vector<pair<int, int> > adj[MAX_N];
vector<pair<int, pair<int, int> > > EdgeList;

int root(int x) {
    return (x == par[x]) ? x : par[x] = root(par[x]);
}

bool same(int x, int y) {
    return root(x) == root(y);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> V >> E >> Q;
    for(int i = 1; i <= V; i++)
        par[i] = i;

    for(int i = 0; i < E; i++) {
        int x, y, w; cin >> x >> y >> w;
        EdgeList.push_back({w, {x, y}});
    }
    // Maximum Spanning Tree (Kruskhal)
    sort(EdgeList.begin(), EdgeList.end(), greater<pair<int, pair<int, int> > >());
    for(int i = 0; i < E; i++) {
        int x = EdgeList[i].second.first, y = EdgeList[i].second.second, w = EdgeList[i].first;
        if(!same(x, y)) { //unite
            par[root(x)] = root(y);
            adj[x].push_back({y, w});
            adj[y].push_back({x, w});
        }
    }
    // Dijkstra
    priority_queue<pair<int, int> > pq;
    dist[1] = INF; pq.push({0, 1});
    while(!pq.empty()) {
        int u = pq.top().second, d = pq.top().first; pq.pop();
        if (d > dist[u]) continue;
        for(int i = 0; i < adj[u].size(); i++){
            int v = adj[u][i].first, w = adj[u][i].second;
            if (dist[v] < min(dist[u], w)){
                dist[v] = min(dist[u], w);
                pq.push({dist[v],v});
            }
        }
    }
    // Answering queries
    while(Q--){
        int x; cin >> x;
        cout << dist[x] << "\n";
    }
}
