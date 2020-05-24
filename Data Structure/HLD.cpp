/*
Heavy-light decomposition (HLD) is a data structure to answer queries and update values on tree
Idea: splitting the trees into separate paths that allows us to use another data structure such as segment tree on a tree
As we decompose the tree, we have enough information to build a lca function (which will be useful as an intermediate step for many types of queries)
For this example, we will answer maximum edge cost query on the path between two nodes
Problem: https://www.spoj.com/problems/QTREE/
*/

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

const int MAX_N = 1e4 + 5;

int N, pos;
int par[MAX_N], num_child[MAX_N], dep[MAX_N];
int chainNum, chainSize[MAX_N], chainHead[MAX_N], chainId[MAX_N], chainPos[MAX_N];
int arr[MAX_N], st_pos[MAX_N], st[4 * MAX_N];
pair<int, int> edges[MAX_N];
vector<pair<int, int>> adj[MAX_N];

void build(int node, int start, int end) { // construct the segment tree using arr
    if (start == end)
        st[node] = arr[start];
    else {
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        st[node] = max(st[2 * node], st[2 * node + 1]);
    }
}

void update_st(int node, int start, int end, int idx, int val) { // node set update
    if (start == end) st[node] = val;
    else {
        int mid = (start + end) / 2;
        if (idx <= mid) update_st(2 * node, start, mid, idx, val);
        else update_st(2 * node + 1, mid + 1, end, idx, val);
        st[node] = max(st[2 * node], st[2 * node + 1]);
    }
}

int query_st(int node, int start, int end, int l, int r) { // range max query on the segment tree
    if (l > r) return 0;
    if (start == l && end == r) return st[node];
    int mid = (start + end) / 2;
    return max(query_st(2 * node, start, mid, l, min(r, mid)),
               query_st(2 * node + 1, mid + 1, end, max(l, mid + 1), r));
}

void dfs(int u = 1, int p = -1, int d = 0) {
    par[u] = p;
    num_child[u] = 1;
    dep[u] = d;
    for (auto next : adj[u]) {
        int v = next.first, w = next.second;
        if (v != p) {
            dfs(v, u, d + 1);
            num_child[u] += num_child[v];
        }
    }
}

// there is no edge associated with node 1 (root), so set val to 0
void hld(int u = 1, int val = 0) { // can pass in more information depending on the type of queries needed
    if (chainHead[chainNum] == -1) chainHead[chainNum] = u; // assign chain head
    chainId[u] = chainNum;
    chainPos[u] = chainSize[chainNum];
    chainSize[chainNum]++;

    st_pos[u] = ++pos;
    arr[pos] = val;

    int heaviest = -1, max_cost;
    for (auto next : adj[u]) {
        int v = next.first, w = next.second;
        if (v != par[u])
            if (heaviest == -1 || num_child[v] > num_child[heaviest]) // find the heaviest path from node u
                heaviest = v, max_cost = w;
    }

    if (heaviest != -1) // if not leaf node, then extend the chain
        hld(heaviest, max_cost);

    for (auto next : adj[u]) { // extend to all other light paths
        int v = next.first, w = next.second;
        if (v != par[u] && v != heaviest) {
            chainNum++;
            hld(v, w);
        }
    }
}

void update(int idx, int val) {
    int u = edges[idx].first, v = edges[idx].second; // representative of an edge is the node that is further away from the root
    int node = dep[u] > dep[v] ? u : v;
    update_st(1, 1, N, st_pos[node], val);
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

int query_up(int u, int mid) { // mid is the ancestor of u (lca of u and v)
	int res = 0	;
	while (true) {
		if (u == mid) break;
		if (chainId[u] == chainId[mid]) { // same chain
			res = max(res, query_st(1, 1, N, st_pos[mid] + 1, st_pos[u])); // remember to +1, you should know why
			break;
		}
		res = max(res, query_st(1, 1, N, st_pos[chainHead[chainId[u]]], st_pos[u]));
		u = par[chainHead[chainId[u]]];
	}
    return res;
}

int query(int u, int v) { // maximum edge cost from u to v
    int mid = lca(u, v); // first find the lca
    return max(query_up(u, mid), query_up(v, mid));
}

void clear_data() { // must do it at the beginning of every test case
    memset(st, 0, sizeof st);
    memset(chainHead, -1, sizeof chainHead);
    for (int i = 1; i <= N; i++) adj[i].clear();
    chainNum = pos = 0;
}

void solve() {
    clear_data();
    cin >> N;
    for (int i = 1; i <= N - 1; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v, w}); adj[v].push_back({u, w});
        edges[i] = {u, v};
    }
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
