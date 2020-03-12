/*
Floyd Warshall algorithm to find all pair shortest paths
Time complexity: O(V^3), can use for V <= 400
Easier to use with adjacency matrix instead of adjacency list
*/

#include <bits/stdc++.h>

using namespace std;

const int INF = 1 << 30;
const int MAX_N = 400 + 5;
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
int dist[MAX_N][MAX_N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
  
    cin >> V >> E;
    for(int i = 0; i < V; i++)
        for(int j = 0; j < V; j++)
            dist[i][j] = (i == j) ? 0 : INF;
    
    for(int i = 0; i < E; i++) {
        int x, y, w; cin >> x >> y >> w;
        dist[x][y] = dist[y][x] = w;
    }
    
    // Very easy to mermorise, only 4 lines
    for(int k = 0; k < V; k++)
        for(int i = 0; i < V; i++)
            for(int j = 0; j < V; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);                
}
