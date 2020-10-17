#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

// DSU standard
struct DSU { 
    vector<int> p, sz;
    DSU(int n) {
        p.resize(n); for (int i = 0; i < n; i++) p[i] = i;
        sz.assign(n, 1);
    }
    int find(int u) {return u == p[u] ? u : p[u] = find(p[u]);}
    bool same(int u, int v) {return find(u) == find(v);}
    void merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return;
        if (sz[u] > sz[v]) swap(u, v);
        sz[v] += sz[u];
        p[u] = v;
    }
};

// DSU with rollback
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
        u = find(u), v = find(v);
        if (u == v) return;
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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
}