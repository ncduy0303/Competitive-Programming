// Heavy-light decomposition (HLD) is a data structure to answer queries and update values on tree
// Splitting the trees into separate paths that allows us to use another data structure such as segment tree on a tree
// As we decompose the tree, we have enough information to build a lca function (which will be useful as an intermediate step for many types of queries)
// For this example, we will answer maximum edge cost query on the path between two nodes
// Problem link: https://www.spoj.com/problems/QTREE/

// Each edge is represented by the node that is further away to the root
// => Each node is associated only one unique edge, except the root node

// sz[u] = size of the subtree of u
// par[u] = parent node of u
// dep[u] = distance of u from the root

// chainNum = number of decomposed chains
// chainSize[s] = number of nodes in chain s
// chainHead[s] = the node closest to the root in chain s
// chainId[u] = the chain that node u belongs to
// chainPos[u] = the position of node u in the chain it belongs to (aka chainInd[u])

// adj: adjacency list
// el: edge list

// arr: array storing edge costs based on HLD
// pos: position of edges based on HLD
// st: segment tree

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e4 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

struct segtree { 
    struct tdata {
        ll mx;
        tdata(): mx() {}
        tdata(ll val): mx(val) {}
        tdata(tdata l, tdata r): mx(max(l.mx, r.mx)) {}
    };
    int ln(int node) {return 2 * node;}
    int rn(int node) {return 2 * node + 1;}
    int n; vector<tdata> st;
    void init(int _n) {
        n = _n;
        st.resize(4 * n);
    }
    void init(vector<int> &arr) {
        n = arr.size();
        st.resize(4 * n);
        build(arr, 1, 0, n - 1);
    }
    void apply(int node, ll val) {
        st[node].mx = val;
    }
    void combine(int node) {
        st[node].mx = max(st[ln(node)].mx, st[rn(node)].mx);
    }
    void build(vector<int> &arr, int node, int start, int end) {
        if (start == end) {
            st[node] = tdata(arr[start]);
            return;
        }
        int mid = (start + end) / 2;
        build(arr, ln(node), start, mid);
        build(arr, rn(node), mid + 1, end);
        combine(node);
    }
    void update(int node, int start, int end, int idx, ll val) {
        if (start == end) {
            apply(node, val);
            return;
        }
        int mid = (start + end) / 2;
        if (idx <= mid) update(ln(node), start, mid, idx, val);
        else update(rn(node), mid + 1, end, idx, val);
        combine(node);
    }
    tdata query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return tdata();
        if (l <= start && end <= r) return st[node];
        int mid = (start + end) / 2;
        return tdata(query(ln(node), start, mid, l, r), query(rn(node), mid + 1, end, l, r));
    }
    void update(int idx, ll val) {update(1, 0, n - 1, idx, val);}
    tdata query(int l, int r) {return query(1, 0, n - 1, l, r);}
};

int n, cnt;
int sz[MAX_N], dep[MAX_N], par[MAX_N], child[MAX_N];
int chainNum, chainHead[MAX_N], chainSize[MAX_N], chainId[MAX_N], chainPos[MAX_N];
vector<int> arr; int pos[MAX_N];
vector<ar<int,2>> adj[MAX_N], el;
segtree st;
 
void reset() {
    memset(chainHead, -1, sizeof chainHead);
    arr.clear();
    for (int i = 1; i <= n; i++) adj[i].clear();
    el.clear();
    chainNum = cnt = 0;
}
 
void dfs(int u, int p = 0, int d = 0) {
    sz[u] = 1;
    dep[u] = d;
    par[u] = p;
    int mx = 0;
    for (auto [v, w] : adj[u]) {
        if (v != p) {
            dfs(v, u, d + 1);
            sz[u] += sz[v];
            if (sz[v] > mx) mx = sz[v], child[u] = v;
        }
    }
}

void hld(int u, int x = -INF) {
    if (chainHead[chainNum] == -1) chainHead[chainNum] = u;
    chainId[u] = chainNum;
    chainPos[u] = chainSize[chainNum]++;
    arr.push_back(x);
    pos[u] = cnt++;
    for (auto [v, w] : adj[u]) {
        if (v != par[u] && v == child[u]) {
            hld(v, w);
        }
    }
    for (auto [v, w] : adj[u]) {
        if (v != par[u] && v != child[u]) {
            chainNum++, hld(v, w);
        }
    }
}
 
int lca(int u, int v) {
    while (chainId[u] != chainId[v]) {
        if (dep[chainHead[chainId[u]]] > dep[chainHead[chainId[v]]]) u = par[chainHead[chainId[u]]];
        else v = par[chainHead[chainId[v]]];
    }
    return dep[u] > dep[v] ? v : u;
}
 
ll query_up(int u, int m) {
    ll res = 0;
    while (true) {
        if (u == m) break;
        if (chainId[u] == chainId[m]) {
            res = max(res, st.query(pos[m] + 1, pos[u]).mx);
            break;
        }
        res = max(res, st.query(pos[chainHead[chainId[u]]], pos[u]).mx);
        u = par[chainHead[chainId[u]]];        
    }
    return res;
}
 
ll query(int u, int v) {
    int m = lca(u, v);
    return max(query_up(u, m), query_up(v, m));
}
 
void update(int i, int x) {
    auto [u, v] = el[i];
    if (dep[u] < dep[v]) swap(u, v);
    st.update(pos[u], x);
}
 
void solve() {
    cin >> n;
    reset();
    for (int i = 0; i < n - 1; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
        el.push_back({u, v});
    }
    dfs(1);
    hld(1);
    st.init(arr);
    while (true) {
        string t; cin >> t;
        if (t == "CHANGE") {
            int i, x; cin >> i >> x; i--;
            update(i, x);
        }
        else if (t == "QUERY") {
            int u, v; cin >> u >> v;
            cout << query(u, v) << "\n";
        }
        else return;
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