// Segment tree beats for chmax, chmin and add range updates
// Problem link: https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum

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

void solve() {
    int n, q; cin >> n >> q;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    segtree st(a);
    while (q--) {
        int t, l, r; cin >> t >> l >> r; r--;
        if (t == 0) {
            ll x; cin >> x;
            st.update_min(l, r, x);
        }
        else if (t == 1) {
            ll x; cin >> x;
            st.update_max(l, r, x);
        }
        else if (t == 2) {
            ll x; cin >> x;
            st.update_add(l, r, x);
        }
        else {
            cout << st.query(l, r).sum << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int tc = 1;
    // cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t  << ": ";
        solve();
    }
}