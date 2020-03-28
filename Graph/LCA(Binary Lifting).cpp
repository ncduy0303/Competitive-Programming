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

int N, Q, dp[MAX_N][MAX_L + 1], tin[MAX_N], tout[MAX_N], timer = 0;
bool visited[MAX_N] = {false};
vector<int> adj[MAX_N];

void dfs(int u, int p) {
    if(visited[u]) return;
    visited[u] = true;
    
    tin[u] = timer++;
    dp[u][0] = p; // direct parent (2^0 = 1)
    
    for(int i = 1; i <= MAX_L; i++) 
        dp[u][i] = dp[dp[u][i - 1]][i - 1];
    
    for(int v : adj[u])
        if(!visited[v])
            dfs(v, u);
    
    tout[u] = timer++;
}

bool is_ancestor(int u, int v){ // check if u is an ancestor of v
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int LCA(int u, int v) {
    if(is_ancestor(u, v)) return u;
    if(is_ancestor(v, u)) return v;
    
    for (int i = MAX_L; i >= 0; i--)
        if (!is_ancestor(dp[u][i], v))
            u = dp[u][i];
    
    return dp[u][0];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    
    cin >> N >> Q;
    for(int i = 0; i < N - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    while(Q--) {
        int u, v; cin >> u >> v;
        printf("LCA of %d and %d is %d\n", u, v, LCA(u, v));
    }
}
