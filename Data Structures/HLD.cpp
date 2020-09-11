// Heavy-light decomposition (HLD) is a data structure to answer queries and update values on tree
// Splitting the trees into separate paths that allows us to use another data structure such as segment tree on a tree
// As we decompose the tree, we have enough information to build a lca function (which will be useful as an intermediate step for many types of queries)
// For this example, we will answer maximum edge cost query on the path between two nodes
// Problem link: https://www.spoj.com/problems/QTREE/

// Each edge is represented by the node that is further away to the root
// => Each node is associated only one unique edge, except the root node

// num_child[u] = number of children the u (including itself)
// par[u] = parent node of u
// dep[u] = distance of u from the root

// chainNum = number of decomposed chains
// chainSize[s] = number of nodes in chain s
// chainHead[s] = the node closest to the root in chain s
// chainId[u] = the chain that node u belongs to
// chainPos[u] = the position of node u in the chain it belongs to (aka chainInd[u])

// adj: adjacency list
// edges: edge list

// arr: array storing edge costs based on HLD
// st_pos: position of edges based on HLD
// st: segment tree

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e4 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

int n, pos;
int par[MAX_N], num_child[MAX_N], dep[MAX_N];
int chainNum, chainSize[MAX_N], chainHead[MAX_N], chainId[MAX_N], chainPos[MAX_N];
int arr[MAX_N], st_pos[MAX_N], st[4 * MAX_N];
ar<int,2> edges[MAX_N];
vector<ar<int,2>> adj[MAX_N];

void build_st(int node, int start, int end) { 
    if (start == end) {
        st[node] = arr[start];
        return;
    }
    int mid = (start + end) / 2;
    build_st(2 * node, start, mid);
    build_st(2 * node + 1, mid + 1, end);
    st[node] = max(st[2 * node], st[2 * node + 1]);
}

void update_st(int node, int start, int end, int idx, int val) { 
    if (start == end) {
        st[node] = val;
        return;
    }
    int mid = (start + end) / 2;
    if (idx <= mid) update_st(2 * node, start, mid, idx, val);
    else update_st(2 * node + 1, mid + 1, end, idx, val);
    st[node] = max(st[2 * node], st[2 * node + 1]);
}

int query_st(int node, int start, int end, int l, int r) {
    if (start > r || end < l) return 0;
    if (l <= start && end <= r) return st[node];
    int mid = (start + end) / 2;
    return max(query_st(2 * node, start, mid, l, r), query_st(2 * node + 1, mid + 1, end, l, r)); 
}

void dfs(int u = 1, int p = 0, int d = 0) {
    par[u] = p;
    num_child[u] = 1;
    dep[u] = d;
    for (auto [v, w] : adj[u]) {
        if (v != p) {
            dfs(v, u, d + 1);
            num_child[u] += num_child[v];
        }
    }
}

// there is no edge associated with node 1 (root), so set val to 0
// can pass in more information depending on the type of queries neede
void hld(int u = 1, int val = 0) { 
    if (chainHead[chainNum] == -1) chainHead[chainNum] = u; 
    chainId[u] = chainNum;
    chainPos[u] = chainSize[chainNum];
    chainSize[chainNum]++;

    st_pos[u] = ++pos;
    arr[pos] = val;

    int heaviest = -1, max_cost;
    for (auto [v, w] : adj[u]) 
        if (v != par[u])
            // find the heaviest path from node u
            if (heaviest == -1 || num_child[v] > num_child[heaviest]) 
                heaviest = v, max_cost = w;

    // if not leaf node, then extend the chain
    if (heaviest != -1) 
        hld(heaviest, max_cost);
    // extend to all other light paths
    for (auto [v, w] : adj[u]) { 
        if (v != par[u] && v != heaviest) {
            chainNum++;
            hld(v, w);
        }
    }
}

void update(int idx, int val) {
    // representative of an edge is the node that is further away from the root
    auto [u, v] = edges[idx]; 
    int node = dep[u] > dep[v] ? u : v;
    update_st(1, 1, n, st_pos[node], val);
}

int lca(int u, int v) {
    // bring u and v to the same chain, then one must be the lca of the other
    while (chainId[u] != chainId[v]) { 
        if (dep[chainHead[chainId[u]]] > dep[chainHead[chainId[v]]])
            u = par[chainHead[chainId[u]]];
        else
            v = par[chainHead[chainId[v]]];
    }
    return dep[u] < dep[v] ? u : v;
}

// mid is the ancestor of u (lca of u and v)
int query_up(int u, int mid) { 
	int res = 0	;
	while (true) {
		if (u == mid) break;
		if (chainId[u] == chainId[mid]) { 
			res = max(res, query_st(1, 1, n, st_pos[mid] + 1, st_pos[u])); 
			break;
		}
		res = max(res, query_st(1, 1, n, st_pos[chainHead[chainId[u]]], st_pos[u]));
		u = par[chainHead[chainId[u]]];
	}
    return res;
}

// maximum edge cost from u to v
int query(int u, int v) { 
    int mid = lca(u, v); 
    return max(query_up(u, mid), query_up(v, mid));
}

void reset() { 
    memset(st, 0, sizeof st);
    memset(chainHead, -1, sizeof chainHead);
    for (int i = 1; i <= n; i++) adj[i].clear();
    chainNum = 1; pos = 0;
}

void solve() {
    reset();
    cin >> n;
    for (int i = 1; i <= n - 1; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v, w}); 
        adj[v].push_back({u, w});
        edges[i] = {u, v};
    }
    dfs();
    hld();
    build_st(1, 1, n);
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
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int tc; cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t  << ": ";
        solve();
    }
}