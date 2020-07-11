// Lazy Propagation
// range_add
// range_sum_query
// Problem link: https://www.spoj.com/problems/HORRIBLE/
// Not using the down function separately (aka lazy propagation)

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 1e5 + 5;

struct tdata {
    ll sum, lazy;
};

int N, Q, arr[MAX_N];
tdata st[4 * MAX_N];

void build(int node, int start, int end) {
    if (start == end) {
        st[node].sum = arr[start];
        st[node].lazy = 0;
    }
    else {
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        st[node].sum = st[2 * node].sum + st[2 * node + 1].sum;
    }
}

void update(int node, int start, int end, int l, int r, ll val) { // increase all members in [l, r] by val
    // always do propagation at the start
    if (st[node].lazy) {
        st[node].sum += st[node].lazy * (end - start + 1);
        if (start != end) {
            st[2 * node].lazy += st[node].lazy;
            st[2 * node + 1].lazy += st[node].lazy;
        }
        st[node].lazy = 0;
    }

    if (r < start || end < l) return;
    if (l <= start && end <= r) {
        st[node].sum += val * (end - start + 1);
        if (start != end) {
            st[2 * node].lazy += val;
            st[2 * node + 1].lazy += val;
        }
    }
    else {
        int mid = (start + end) / 2;
        update(2 * node, start, mid, l, r, val);
        update(2 * node + 1, mid + 1, end, l, r, val);
        st[node].sum = st[2 * node].sum + st[2 * node + 1].sum;
    }
}

ll query(int node, int start, int end, int l, int r) {
    // always do propagation at the start
    if (st[node].lazy) {
        st[node].sum += st[node].lazy * (end - start + 1);
        if (start != end) {
            st[2 * node].lazy += st[node].lazy;
            st[2 * node + 1].lazy += st[node].lazy;
        }
        st[node].lazy = 0;
    }

    if (r < start || end < l) return 0;
    if (l <= start && end <= r) return st[node].sum;
    else {
        int mid = (start + end) / 2;
        return query(2 * node, start, mid, l, r) + query(2 * node + 1, mid + 1, end, l, r);
    }
}

void solve() {
    memset(st, 0, sizeof st);
    cin >> N >> Q;
    build(1, 1, N);
    while (Q--) {
        char c; cin >> c;
        if (c == '0') {
            int l, r; ll val; cin >> l >> r >> val;
            update(1, 1, N, l, r, val);
        }
        else {
            int l, r; cin >> l >> r;
            cout << query(1, 1, N, l, r) << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int tc; cin >> tc;
    while (tc--) {
        solve();
    }
}
