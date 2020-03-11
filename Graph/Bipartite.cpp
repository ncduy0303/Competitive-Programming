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
vector<int> adj[MAX_N];

bool isBipartite() { //applying BFS and assigning colour to each node
    queue<int> Q; int colour[V];
    memset(colour, -1, sizeof colour);
    Q.push(0); colour[0] = 0;
    
    while(!Q.empty()) {
        int u = Q.front(); Q.pop();
        for(int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];
            if(colour[v] == -1) {
                colour[v] = 1 - colour[u];
                Q.push(v);
            }
            else if(colour[v] == colour[u]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
  
    cin >> V >> E;
    for(int i = 0; i < E; i++) {
        int x, y; cin >> x >> y;
        adj[x].push_back(y); adj[y].push_back(x);
    }
    
    memset(dist, -1, sizeof dist);
    Q.push(0); dist[0] = 0;
    while(!Q.empty()) {
        int u = Q.front(); Q.pop();
        for(int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];
            if(dist[v] == -1) {
                dist[v] = dist[u] + 1;
                Q.push(v);
            }
        }
    }
}
