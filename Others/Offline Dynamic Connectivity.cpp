// Use DSU (with rollback) to solve offline dynamic connectivity problems
// Time complexity: O(qlogqlogn)
// Problem link: https://dunjudge.me/analysis/problems/422/

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 3e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

struct DSU {
    int num;
    vector<int> p, sz;
    stack<int> st;
    void init(int n) {
        num = n;
        p.resize(n); for (int i = 0; i < n; i++) p[i] = i;
        sz.assign(n, 1);
    }
    int find(int u) {return u == p[u] ? u : find(p[u]);}
    bool same(int u, int v) {return find(u) == find(v);}
    void merge(int u, int v) {
        if (same(u, v)) return;
        u = find(u), v = find(v);
        if (sz[u] > sz[v]) swap(u, v);
        num--;
        sz[v] += sz[u];
        p[u] = v;
        st.push(u);
    }
    void rollback(int t) {
        while (st.size() > t) {
            int u = st.top(); st.pop();
            num++;
            sz[p[u]] -= sz[u];
            p[u] = u;
        }
    }
};

int n, m, q, us[MAX_N], vs[MAX_N], other[MAX_N], ans[MAX_N];
vector<ar<int,5>> qs; // {time, type, id, u, v}
map<ar<int,2>,int> mp;
DSU uf;

void dco(int l, int r) {
    if (l > r) return;
    if (l == r) {
        auto [t, c, id, u, v] = qs[l];
        if (c == 2) ans[id] = uf.same(u, v);
        return;
    }
    int mid = (l + r) / 2;
    int save = uf.st.size();
    for (int i = mid + 1; i <= r; i++) {
        auto [t, c, id, u, v] = qs[i];
        if (c == 1 && other[i] < l) { // query covers [l, mid]
            uf.merge(u, v);
        } 
    }
    dco(l, mid);
    uf.rollback(save);
    for (int i = l; i <= mid; i++) {
        auto [t, c, id, u, v] = qs[i];
        if (c == 0 && other[i] > r) { // query covers [mid + 1, r]
            uf.merge(u, v);
        } 
    }
    dco(mid + 1, r);
    uf.rollback(save);
}

void solve() {
    cin >> n >> m; uf.init(n);
    for (int i = 0; i < m; i++) {
        int u, v, s, e; cin >> u >> v >> s >> e;
        qs.push_back({s, 0, -1, u, v});
        qs.push_back({e + 1, 1, -1, u, v});
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        int u, v, t; cin >> u >> v >> t;
        qs.push_back({t, 2, i, u, v});
    }
    sort(qs.begin(), qs.end());
    for (int i = 0; i < qs.size(); i++) {
        auto [t, c, id, u, v] = qs[i];
        if (c == 0) {
            mp[{u, v}] = i;
            other[i] = qs.size();
        }
        if (c == 1) {
            other[mp[{u, v}]] = i;
            other[i] = mp[{u, v}];
        }
    }
    dco(0, qs.size() - 1);
    for (int i = 0; i < q; i++) {
        cout << (ans[i] ? "Y" : "N") << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int tc; tc = 1;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t  << ": ";
        solve();
    }
}