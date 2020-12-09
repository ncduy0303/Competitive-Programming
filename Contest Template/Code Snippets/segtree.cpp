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

// segment tree beats
#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

struct segtree { 
    struct tdata {
        ll sum, addval, mx, mx2, mx_cnt, mn, mn2, mn_cnt;
        tdata(): sum(), addval(), mx(-LINF), mx2(-LINF), mx_cnt(), mn(LINF), mn2(LINF), mn_cnt() {}
        tdata(ll val): sum(val), addval(), mx(val), mx2(-LINF), mx_cnt(1), mn(val), mn2(LINF), mn_cnt(1) {}
        tdata(tdata l, tdata r) {
            sum = l.sum + r.sum;
            if (l.mx > r.mx) {
                mx = l.mx;
                mx2 = max(l.mx2, r.mx);
                mx_cnt = l.mx_cnt;
            }
            else if (r.mx > l.mx) {
                mx = r.mx;
                mx2 = max(r.mx2, l.mx);
                mx_cnt = r.mx_cnt;
            }
            else {
                mx = l.mx;
                mx2 = max(l.mx2, r.mx2);
                mx_cnt = l.mx_cnt + r.mx_cnt;
            }
            if (l.mn < r.mn) {
                mn = l.mn;
                mn2 = min(l.mn2, r.mn);
                mn_cnt = l.mn_cnt;
            }
            else if (r.mn < l.mn) {
                mn = r.mn;
                mn2 = min(r.mn2, l.mn);
                mn_cnt = r.mn_cnt;
            }
            else {
                mn = l.mn;
                mn2 = min(l.mn2, r.mn2);
                mn_cnt = l.mn_cnt + r.mn_cnt;
            }
        }
    };
    int ln(int node) {return 2 * node;}
    int rn(int node) {return 2 * node + 1;}
    int n; vector<tdata> st;
    segtree(int n): n(n), st(4 * n) {}
    segtree(vector<ll> &arr) : segtree(arr.size()) {
        build(arr, 1, 0, n - 1);
    }
    void apply_add(int node, int start, int end, ll val) {
        st[node].sum += val * (end - start + 1);
        st[node].mx += val;
        st[node].mn += val;
        if (st[node].mx2 != -LINF) st[node].mx2 += val; 
        if (st[node].mn2 != LINF) st[node].mn2 += val; 
        st[node].addval += val;
    }
    void apply_min(int node, ll val) {
        st[node].sum += (val - st[node].mx) * st[node].mx_cnt;
        st[node].mx = val;
        if (val < st[node].mn) st[node].mn = val;
        else if (val < st[node].mn2) st[node].mn2 = val;
    }
    void apply_max(int node, ll val) {
        st[node].sum += (val - st[node].mn) * st[node].mn_cnt;
        st[node].mn = val;
        if (val > st[node].mx) st[node].mx = val;
        else if (val > st[node].mx2) st[node].mx2 = val;
    }
    void combine(int node) {
        st[node].sum = st[ln(node)].sum + st[rn(node)].sum;
        if (st[ln(node)].mx > st[rn(node)].mx) {
            st[node].mx = st[ln(node)].mx;
            st[node].mx2 = max(st[ln(node)].mx2, st[rn(node)].mx);
            st[node].mx_cnt = st[ln(node)].mx_cnt;
        }
        else if (st[rn(node)].mx > st[ln(node)].mx) {
            st[node].mx = st[rn(node)].mx;
            st[node].mx2 = max(st[rn(node)].mx2, st[ln(node)].mx);
            st[node].mx_cnt = st[rn(node)].mx_cnt;
        }
        else {
            st[node].mx = st[ln(node)].mx;
            st[node].mx2 = max(st[ln(node)].mx2, st[rn(node)].mx2);
            st[node].mx_cnt = st[ln(node)].mx_cnt + st[rn(node)].mx_cnt;
        }
        if (st[ln(node)].mn < st[rn(node)].mn) {
            st[node].mn = st[ln(node)].mn;
            st[node].mn2 = min(st[ln(node)].mn2, st[rn(node)].mn);
            st[node].mn_cnt = st[ln(node)].mn_cnt;
        }
        else if (st[rn(node)].mn < st[ln(node)].mn) {
            st[node].mn = st[rn(node)].mn;
            st[node].mn2 = min(st[rn(node)].mn2, st[ln(node)].mn);
            st[node].mn_cnt = st[rn(node)].mn_cnt;
        }
        else {
            st[node].mn = st[ln(node)].mn;
            st[node].mn2 = min(st[ln(node)].mn2, st[rn(node)].mn2);
            st[node].mn_cnt = st[ln(node)].mn_cnt + st[rn(node)].mn_cnt;
        }
    }
    void propagate(int node, int start, int end) {
        if (start == end) return;
        int mid = (start + end) / 2;
        if (st[node].addval) {
            apply_add(ln(node), start, mid, st[node].addval);
            apply_add(rn(node), mid + 1, end, st[node].addval);
            st[node].addval = 0;
        }
        if (st[node].mx < st[ln(node)].mx) apply_min(ln(node), st[node].mx);
        if (st[node].mx < st[rn(node)].mx) apply_min(rn(node), st[node].mx);
        if (st[node].mn > st[ln(node)].mn) apply_max(ln(node), st[node].mn);
        if (st[node].mn > st[rn(node)].mn) apply_max(rn(node), st[node].mn);
    }
    void build(vector<ll> &arr, int node, int start, int end) {
        if (start == end) {
            st[node] = tdata(arr[start]);
            return;
        }
        int mid = (start + end) / 2;
        build(arr, ln(node), start, mid);
        build(arr, rn(node), mid + 1, end);
        combine(node);
    }
    void update_add(int node, int start, int end, int l, int r, ll val) {
        propagate(node, start, end);
        if (r < start || end < l) return;
        if (l <= start && end <= r) {
            apply_add(node, start, end, val);
            return;
        }
        int mid = (start + end) / 2;
        update_add(ln(node), start, mid, l, r, val);
        update_add(rn(node), mid + 1, end, l, r, val);
        combine(node);
    }
    void update_min(int node, int start, int end, int l, int r, ll val) {
        propagate(node, start, end);
        if (r < start || end < l || st[node].mx <= val) return;
        if (l <= start && end <= r && st[node].mx2 < val) {
            apply_min(node, val);
            return;
        }
        int mid = (start + end) / 2;
        update_min(ln(node), start, mid, l, r, val);
        update_min(rn(node), mid + 1, end, l, r, val);
        combine(node);
    }
    void update_max(int node, int start, int end, int l, int r, ll val) {
        propagate(node, start, end);
        if (r < start || end < l || st[node].mn >= val) return;
        if (l <= start && end <= r && st[node].mn2 > val) {
            apply_max(node, val);
            return;
        }
        int mid = (start + end) / 2;
        update_max(ln(node), start, mid, l, r, val);
        update_max(rn(node), mid + 1, end, l, r, val);
        combine(node);
    }
    tdata query(int node, int start, int end, int l, int r) {
        propagate(node, start, end);
        if (r < start || end < l) return tdata();
        if (l <= start && end <= r) return st[node];
        int mid = (start + end) / 2;
        return tdata(query(ln(node), start, mid, l, r), query(rn(node), mid + 1, end, l, r));
    }
    void update_add(int l, int r, ll val) {update_add(1, 0, n - 1, l, r, val);}
    void update_min(int l, int r, ll val) {update_min(1, 0, n - 1, l, r, val);}
    void update_max(int l, int r, ll val) {update_max(1, 0, n - 1, l, r, val);}
    tdata query(int l, int r) {return query(1, 0, n - 1, l, r);}
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
}