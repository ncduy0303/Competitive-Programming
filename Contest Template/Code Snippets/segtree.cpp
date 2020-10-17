// Use 0-index

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

// standard segment tree (range set, range sum, lazy propagation)
struct segtree { 
    struct tdata {
        ll sum, setval;
        tdata(): sum(), setval(LINF) {}
        tdata(ll val): sum(val), setval(LINF) {}
        tdata(tdata l, tdata r): sum(l.sum + r.sum), setval(LINF) {}
    };
    int ln(int node) {return 2 * node;}
    int rn(int node) {return 2 * node + 1;}
    int n; vector<tdata> st;
    segtree(int n): n(n), st(4 * n) {}
    segtree(vector<int> arr) : segtree(arr.size()) {
        build(arr, 1, 0, n - 1);
    }
    void apply(int node, int start, int end, ll val) {
        st[node].sum = val * (end - start + 1);
        st[node].setval = val;
    }
    void combine(int node) {
        st[node].sum = st[ln(node)].sum + st[rn(node)].sum;
    }
    void propagate(int node, int start, int end) {
        if (start == end || st[node].setval == LINF) return;
        int mid = (start + end) / 2;
        apply(ln(node), start, mid, st[node].setval);
        apply(rn(node), mid + 1, end, st[node].setval);
        st[node].setval = LINF;
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
        propagate(node, start, end);
        if (start == end) {
            apply(node, start, end, val);
            return;
        }
        int mid = (start + end) / 2;
        if (idx <= mid) update(ln(node), start, mid, idx, val);
        else update(rn(node), mid + 1, end, idx, val);
        combine(node);
    }
    void update(int node, int start, int end, int l, int r, ll val) {
        propagate(node, start, end);
        if (r < start || end < l) return;
        if (l <= start && end <= r) {
            apply(node, start, end, val);
            return;
        }
        int mid = (start + end) / 2;
        update(ln(node), start, mid, l, r, val);
        update(rn(node), mid + 1, end, l, r, val);
        combine(node);
    }
    tdata query(int node, int start, int end, int l, int r) {
        propagate(node, start, end);
        if (r < start || end < l) return tdata();
        if (l <= start && end <= r) return st[node];
        int mid = (start + end) / 2;
        return tdata(query(ln(node), start, mid, l, r), query(rn(node), mid + 1, end, l, r));
    }
    void update(int idx, ll val) {update(1, 0, n - 1, idx, val);}
    void update(int l, int r, ll val) {update(1, 0, n - 1, l, r, val);}
    tdata query(int l, int r) {return query(1, 0, n - 1, l, r);}
};

// dynamic segment tree (range sum, range set, lazy propagation)
struct segtree { 
    struct tdata {
        tdata *ln, *rn;
        ll start, end, sum, setval;
        tdata(): start(), end(), sum(), setval(LINF) {}
        tdata(int start, int end, ll val): start(start), end(end), sum(val), setval(LINF) {}
        tdata(tdata l, tdata r): start(l.start), end(r.end), sum(l.sum + r.sum), setval(LINF) {}
        void init() {
            if (ln == NULL) {
                int mid = (start + end) / 2;
                ln = new tdata(start, mid, 0), rn = new tdata(mid + 1, end, 0);
            }
        }
    };
    int n; tdata* st;
    segtree(int n): n(n) {
        st = new tdata(0, n - 1, 0);
    }
    void apply(tdata *node, ll val) {
        node->sum = val * (node->end - node->start + 1);
        node->setval = val;
    }
    void combine(tdata *node) {
        node->sum = node->ln->sum + node->rn->sum;
    }
    void propagate(tdata *node) {
        if (node->start == node->end || node->setval == LINF) return;
        node->init();
        apply(node->ln, node->setval);
        apply(node->rn, node->setval);
        node->setval = LINF;
    }
    void update(tdata *node, int idx, ll val) {
        propagate(node);
        if (node->start == node->end) {
            apply(node, val);
            return;
        }
        node->init();
        int mid = (node->start + node->end) / 2;
        if (idx <= mid) update(node->ln, idx, val);
        else update(node->rn, idx, val);
        combine(node);
    }
    void update(tdata *node, int l, int r, ll val) {
        propagate(node);
        if (r < node->start || node->end < l) return;
        if (l <= node->start && node->end <= r) {
            apply(node, val);
            return;
        }
        node->init();
        update(node->ln, l, r, val);
        update(node->rn, l, r, val);
        combine(node);
    }
    tdata query(tdata *node, int l, int r) {
        propagate(node);
        if (r < node->start || node->end < l) return tdata();
        if (l <= node->start && node->end <= r) return *node;
        return tdata(query(node->ln, l, r), query(node->rn, l, r));
    }
    void update(int idx, ll val) {update(st, idx, val);}
    void update(int l, int r, ll val) {update(st, l, r, val);}
    tdata query(int l, int r) {return query(st, l, r);}
};

// persistent segment tree (range sum, range set, lazy propagation, copy)
struct segtree { 
    struct tdata {
        tdata *ln, *rn;
        ll sum, setval;
        tdata(): sum(), setval(LINF) {}
        tdata(ll val): sum(val), setval(LINF) {}
        tdata(tdata *ln, tdata *rn, ll val): ln(ln), rn(rn), sum(val), setval(LINF) {}
        tdata(tdata l, tdata r): sum(l.sum + r.sum), setval(LINF) {}
        void init() {
            if (ln == NULL) {
                ln = new tdata(), rn = new tdata();
            }
        }
    };
    int n, ver; vector<tdata*> st;
    segtree(int n, int q): n(n), ver(), st(q) {
        st[0] = new tdata();
    }
    segtree(vector<int> arr, int q) : segtree(arr.size(), q) {
        build(arr, st[0], 0, n - 1);
    }
    void apply(tdata *node, int start, int end, ll val) {
        node->sum = val * (end - start + 1);
        node->setval = val;
    }
    void combine(tdata *node) {
        node->sum = node->ln->sum + node->rn->sum;
    }
    void propagate(tdata *node, int start, int end) {
        if (start == end || node->setval == LINF) return;
        node->init();
        int mid = (start + end) / 2;
        apply(node->ln, start, mid, node->setval);
        apply(node->rn, mid + 1, end, node->setval);
        node->setval = LINF;
    }
    void build(vector<int> &arr, tdata *node, int start, int end) {
        if (start == end) {
            *node = tdata(arr[start]);
            return;
        }
        node->init();
        int mid = (start + end) / 2;
        build(arr, node->ln, start, mid);
        build(arr, node->rn, mid + 1, end);
        combine(node);
    }
    void update(tdata *node, int start, int end, int idx, ll val) {
        propagate(node, start, end);
        if (start == end) {
            apply(node, start, end, val);
            return;
        }
        int mid = (start + end) / 2;
        if (idx <= mid) {
            node->ln = new tdata(node->ln->ln, node->ln->rn, node->ln->sum);
            update(node->ln, start, mid, idx, val);
        }
        else {
            node->rn = new tdata(node->rn->ln, node->rn->rn, node->rn->sum);
            update(node->rn, mid + 1, end, idx, val);
        }
        combine(node);
    }
    void update(tdata *node, int start, int end, int l, int r, ll val) {
        propagate(node, start, end);
        if (r < start || end < l) return;
        if (l <= start && end <= r) {
            apply(node, start, end, val);
            return;
        }
        int mid = (start + end) / 2;
        node->ln = new tdata(node->ln->ln, node->ln->rn, node->ln->sum);
        node->rn = new tdata(node->rn->ln, node->rn->rn, node->rn->sum);
        update(node->ln, start, mid, l, r, val);
        update(node->rn, mid + 1, end, l, r, val);
        combine(node);
    }
    tdata query(tdata *node, int start, int end, int l, int r) {
        propagate(node, start, end);
        if (r < start || end < l) return tdata();
        if (l <= start && end <= r) return *node;
        int mid = (start + end) / 2;
        return tdata(query(node->ln, start, mid, l, r), query(node->rn, mid + 1, end, l, r));
    }
    void update(int k, int idx, ll val) {update(st[k], 0, n - 1, idx, val);}
    void update(int k, int l, int r, ll val) {update(st[k], 0, n - 1, l, r, val);}
    tdata query(int k, int l, int r) {return query(st[k], 0, n - 1, l, r);}
    void copy(int k) {st[++ver] = new tdata(st[k]->ln, st[k]->rn, st[k]->sum);}
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
}