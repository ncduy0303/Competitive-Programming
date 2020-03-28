/* NOI 2017 - Roadside Advertisements
Idea: LCA(Binary Lifting) + MST(Kruskal) (with reference to solution 4C from the NOI official solution)
Time Complexity: O(NlogN)
*/

#include <bits/stdc++.h>

using namespace std;

const int INF = 1 << 30;
const int MAX_N = 50000 + 5;
const int MAX_L = 20; // ~ Log N
const long long MOD = 1e9 + 7;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) (S & (-S))
#define isBitSet(S, i) ((S >> i) & 1)

int N, Q;

// this is for LCA (Binary Lifting)
int dp[MAX_N][MAX_L], tin[MAX_N], tout[MAX_N];
int timer = 0;
bool visited[MAX_N] = {false};
vector<pair<int, int> > adj[MAX_N];

//this is for MST (Kruskal)
int par[MAX_N];
vector<pair<int, pair<int, int> > > EdgeList;

//this is for the last part
int tmp[5], sum[MAX_N];
vector<int> can;
set<int> nodes;

void dfs(int u, int p, int dist){
    if(visited[u]) return;
    visited[u] = true;

    tin[u] = ++timer;
    sum[u] = dist;
    dp[u][0] = p;

    for (int i = 1; i <= MAX_L; i++)
        dp[u][i] = dp[dp[u][i - 1]][i - 1];

    for(int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i].first, w = adj[u][i].second;
        if(!visited[v])
            dfs(v, u, dist + w);
    }

    tout[u] = timer++;
}

bool is_ancestor(int u, int v){
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int LCA(int u, int v){
    if (is_ancestor(u, v)) return u;
    if (is_ancestor(v, u)) return v;

    for (int i = MAX_L; i >= 0; i--)
        if (!is_ancestor(dp[u][i], v))
            u = dp[u][i];

    return dp[u][0];
}

int root(int x) { //UFDS
    return (x == par[x]) ? x : par[x] = root(par[x]);
}

bool same(int x, int y) {
    return root(x) == root(y);
}

void unite(int x, int y) {
    par[root(x)] = root(y);
}

int Kruskal() {
    int mst_cost = 0;
    sort(EdgeList.begin(), EdgeList.end());
    for(int i = 0; i < EdgeList.size(); i++) {
        par[EdgeList[i].second.first] = EdgeList[i].second.first;
        par[EdgeList[i].second.second] = EdgeList[i].second.second;
    }
    for(int i = 0; i < EdgeList.size(); i++) {
        int x = EdgeList[i].second.first, y = EdgeList[i].second.second, w = EdgeList[i].first;
        if(!same(x, y)) {
            unite(x, y);
            mst_cost += w;
        }
    }
    return mst_cost;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> N;
    for(int i = 0; i < N - 1; i++) {
        int x, y, w; cin >> x >> y >> w;
        adj[x].push_back({y, w}); adj[y].push_back({x, w});
    }

    dfs(0, 0, 0);

    cin >> Q;
    while(Q--){
        nodes.clear(); EdgeList.clear(); can.clear();
        for(int i = 0; i < 5; i++) {
            cin >> tmp[i];
            can.push_back(tmp[i]);
            nodes.insert(tmp[i]);
        }
        //pair-wise LCA between the 5 five nodes
        for(int u = 0; u < 4; u++) {
            for(int v = u + 1; v < 5; v++) {
                int t = LCA(tmp[u], tmp[v]);
                if(nodes.find(t) == nodes.end()) {
                    can.push_back(t);
                    nodes.insert(t);
                }
            }
        }
        for(int u = 0; u < can.size() - 1; u++) {
            for(int v = u + 1; v < can.size(); v++) {
                int t = LCA(can[u], can[v]);
                int cost = sum[can[u]] + sum[can[v]] - (2 * sum[t]);
                EdgeList.push_back({cost, {can[u], can[v]}});
            }
        }
        cout << Kruskal() << "\n";
    }
}
