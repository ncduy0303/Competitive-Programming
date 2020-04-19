// Problem: https://dunjudge.me/analysis/problems/1287/
// Idea: Merging all nodes in each SCC into a new node with new value as the sum of its element's value
// After merging, the graph becomes a DAG, which then can be solved using DP to find the heaviest path starting from S

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

int V, E, S, P, numSCC = 0, visited[MAX_N], cost[MAX_N], newcost[MAX_N], comp[MAX_N], canend[MAX_N], ans = 0;
vector<int> adj[MAX_N], adj_T[MAX_N], dfn, SCC[MAX_N];

void Kosaraju(int u, int pass) {
    visited[u] = 1;
    if (pass == 1) { // 1st pass
        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];
            if (!visited[v]) Kosaraju(v, 1); // first time visited
        }
        dfn.push_back(u);
    }
    else { // 2nd pass
        comp[u] = numSCC;
        for (int i = 0; i < adj_T[u].size(); i++) {
            int v = adj_T[u][i];
            if (!visited[v]) Kosaraju(v, 2); // first time visited
        }
    }
}

int dp[MAX_N]; // dp[i] is the maximum money can be collected if end at the new node i (combination of all nodes in that SCC)
int memo(int x){
    if (x == comp[S]) return newcost[x];
    if (dp[x]) return dp[x];
    int res = -INF;
    for (int i = 0; i < SCC[x].size(); i++)
        res = max(res, memo(SCC[x][i]));

    return dp[x] = res + newcost[x];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> V >> E;
    for (int i = 0; i < E; i++) {
        int x, y; cin >> x >> y;
        adj[x].push_back(y);
        adj_T[y].push_back(x);
    }
    for (int i = 1; i <= V; i++) cin >> cost[i];
    cin >> S >> P;

    // Finding SCC using Kosaraju
    memset(visited, 0, sizeof visited);
    for (int i = 1; i <= V; i++)
        if (!visited[i])
            Kosaraju(i, 1);
    memset(visited, 0, sizeof visited);
    for (int i = V - 1; i >= 0; i--) {
        if (!visited[dfn[i]]) {
            numSCC++;
            Kosaraju(dfn[i], 2);
        }
    }

    // Merging all nodes in each SCC into one single node => The graph becomes a DAG
    for (int i = 1; i <= V; i++) {
        for (int j = 0; j < adj_T[i].size(); j++) {
            if(comp[i] != comp[adj_T[i][j]]) {
                SCC[comp[i]].push_back(comp[adj_T[i][j]]);
            }
        }
        newcost[comp[i]] += cost[i];
    }

    for (int i = 0; i < P; i++) {
        int x; cin >> x;
        canend[comp[x]] = 1;
    }

    for (int i = 1; i <= numSCC; i++)
        if (canend[i])
            ans = max(ans, memo(i));

    cout << ans;
}
