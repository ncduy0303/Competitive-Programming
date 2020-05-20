/*
Heavy-light decomposition (HLD) is a data structure to answer queries and update values on tree
Idea: splitting the trees into separate paths that allows us to use another data structure such as segment tree on a tree
As we decompose the tree, we have enough information to build a lca function (which will be useful as an intermediate step for many types of queries)
For this example, we will answer maximum edge cost query on the path between two nodes
Problem: https://www.spoj.com/problems/QTREE/
*/

// num_child[u] = number of children the u (including itself)
// par[u] = parent node of u
// dep[u] = distance of u from the root

// chainNum = number of decomposed chains
// chainSize[s] = number of nodes in chain s
// chainHead[s] = the node closest to the root in chain s
// chainId[u] = the chain that node u belongs to
// chainPos[u] = the position of node u in the chain it belongs to (aka chainInd[u])

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e4 + 5;
const int MAX_L = 30;
const int MOD = 1e9 + 7;
const int INF = 1e9 + 7;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;

int N, pos = 1;
int num_child[MAX_N], par[MAX_N], dep[MAX_N];
int chainNum = 0, chainSize[MAX_N], chainHead[MAX_N], chainId[MAX_N], chainPos[MAX_N];
int arr[MAX_N], st_pos[MAX_N], st[4 * MAX_N];
vi adj[MAX_N], edges[MAX_N], cost[MAX_N];

void build(int node, int start, int end) {
    if (start == end)
        st[node] = arr[start];
    else {
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        st[node] = max(st[2 * node], st[2 * node + 1]);
    }
}

void update_st(int node, int start, int end, int idx, int val) {
    if (start == end) {
        st[node] = val;
        arr[start] = val;
    }
    else {
        int mid = (start + end) / 2;
        if (idx <= mid) update_st(2 * node, start, mid, idx, val);
        else update_st(2 * node + 1, mid + 1, end, idx, val);
        st[node] = max(st[2 * node], st[2 * node + 1]);
    }
}

int query_st(int node, int start, int end, int l, int r) {
    if (l > r) return -INF;
    if (start == l && end == r) return st[node];

    int mid = (start + end) / 2;
    return max(query_st(2 * node, start, mid, l, min(r, mid)),
               query_st(2 * node + 1, mid + 1, end, max(l, mid + 1), r));
}

void dfs(int u = 1, int p = -1, int d = 0) {
    par[u] = p;
    num_child[u] = 1;
    dep[u] = d;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u, d + 1);
            num_child[u] += num_child[v];
        }
    }
}

void hld(int u = 1, int val = 0) { // can pass in more information depending on the type of queries needed
    if (chainHead[chainNum] == -1) chainHead[chainNum] = u; // assign chain head
    chainId[u] = chainNum;
    chainPos[u] = chainSize[chainNum];
    chainSize[chainNum]++;

    st_pos[u] = pos;
    arr[pos] = val;
    pos++;

    int heaviest = -1, max_cost;
    for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];
        if (v != par[u])
            if (heaviest == -1 || num_child[v] > num_child[heaviest]) // find the heaviest path from node u
                heaviest = v, max_cost = cost[v][i];
    }


    if (heaviest != -1) // if not leaf node, then extend the chain
        hld(heaviest, max_cost);

    for (int i = 0; i < adj[u].size(); i++) { // extend to all other light paths
        int v = adj[u][i];
        if (v != par[u] && v != heaviest)
            chainNum++, hld(v, cost[v][i]);
    }
}

int lca(int u, int v) {
    while (chainId[u] != chainId[v]) { // bring u and v to the same chain, then one must be the lca of the other
        if (dep[chainHead[chainId[u]]] > dep[chainHead[chainId[v]]])
            u = par[chainHead[chainId[u]]];
        else
            v = par[chainHead[chainId[v]]];
    }
    return dep[u] < dep[v] ? u : v;
}

int query_up(int u, int mid) { // mid is the lca of u and v
	int res = 0	;
	while (true) {
		if (u == mid) break;
		if (chainId[u] == chainId[mid]) { // same chain
			res = max(res, query_st(1, 1, N, st_pos[mid] + 1, st_pos[u]));
			break;
		}
		res = max(res, query_st(1, 1, N, st_pos[chainHead[chainId[u]]], st_pos[u]));
		u = par[chainHead[chainId[u]]];
	}
    return res;
}

void update(int idx, int val) { // find the edge position in segment tree and update it
    int u = edges[idx][0], v = edges[idx][1];
    int node = dep[u] > dep[v] ? u : v;
    update_st(1, 1, N, st_pos[node], val);
}

int query(int u, int v) { // maximum edge cost from u to v
    int mid = lca(u, v); // first find the lca
    return max(query_up(u, mid), query_up(v, mid));
}

void solve() {
    cin >> N;
    for (int i = 0; i < MAX_N; i++){
        adj[i].clear();
        cost[i].clear();
        edges[i].clear();
    }
    for (int i = 1; i < N; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back(v);
        adj[v].push_back(u);
        edges[i].push_back(u);
        edges[i].push_back(v);
        cost[u].push_back(w);
        cost[v].push_back(w);
    }
    memset(chainHead, -1, sizeof chainHead);
    memset(st, 0, sizeof st);
    dfs();
    hld();
    build(1, 1, N);
    while (true) {
        string s; cin >> s;
        if (s == "DONE") return;
        if (s == "CHANGE") {
            int idx, val; cin >> idx >> val;
            update(idx, val);
        }
        else {
            int u, v; cin >> u >> v;
            cout << query(u, v) << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int tc; cin >> tc;
    for (int t = 1; t <= tc; t++)
        solve();
}
