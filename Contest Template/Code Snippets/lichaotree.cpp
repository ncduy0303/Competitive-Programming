#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;


// Basic Li-Chao Segment Tree (return minimum)
struct lichaotree{
    struct tdata {
        ll m, c; // y = m * x + c
        tdata() {}
        tdata(ll m, ll c): m(m), c(c) {}
        ll operator()(ll x) {return m * x + c;}
    };
    int ln(int node) {return 2 * node;}
    int rn(int node) {return 2 * node + 1;}
    int n; vector<tdata> st;
    lichaotree(int n): n(n), st(4 * n, {INF, INF}) {}
    void update(int node, int start, int end, tdata y) {
        int mid = (start + end) / 2;
        bool b1 = y(start) < st[node](start);
        bool b2 = y(mid) < st[node](mid);
        if (b2) swap(st[node], y);
        if (start + 1 == end) return;
        if (b1 != b2) update(ln(node), start, mid, y);
        else update(rn(node), mid, end, y);
    }
    ll query(int node, int start, int end, int x) {
        if (start + 1 == end) return st[node](x);
        int mid = (start + end) / 2;
        if (x < mid) return min(st[node](x), query(ln(node), start, mid, x));
        return min(st[node](x), query(rn(node), mid, end, x));
    }
    void update(tdata y) {update(1, 0, n, y);}
    ll query(int x) {return query(1, 0, n, x);}
}; 

// Li-Chao Dynamic Segment Tree (used when range > 1e6)
struct lichaotree {
    struct line {
        ll m, c;
        line(ll m, ll c): m(m), c(c) {}
        ll operator()(ll x) {return m * x + c;}
    };
    struct tdata {
        line seg;
        tdata *ln = NULL, *rn = NULL;
        tdata(line seg): seg(seg) {}
    };
    int n; tdata *st;
    lichaotree(int n): n(n) {st = new tdata({INF, INF});}
    void update(tdata *node, int start, int end, line y) {
        int mid = (start + end) / 2;
        bool b1 = y(start) < node->seg(start);
        bool b2 = y(mid) < node->seg(mid);
        if (b2) swap(node->seg, y);
        if (start + 1 == end) return;
        if (b1 != b2) {
            if (node->ln) update(node->ln, start, mid, y);
            else node->ln = new tdata(y);
        }
        else {
            if (node->rn) update(node->rn, mid, end, y);
            else node->rn = new tdata(y);
        }
    }
    ll query(tdata *node, ll start, ll end, ll x) {
        if (start + 1 == end) return node->seg(x);
        ll mid = (start + end) / 2;
        if (x < mid && node->ln) return min(node->seg(x), query(node->ln, start, mid, x));
        else if (node->rn) return min(node->seg(x), query(node->rn, mid, end, x));
        return node->seg(x);
    }
    void update(line y) {update(st, 0, n, y);}
    ll query(int x) {return query(st, 0, n, x);}
}; 

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
}