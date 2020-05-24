// Lazy Propagation
// range_toggle
// range_count_set_bits_query
// Problem link: https://www.spoj.com/problems/LITE/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 1e5 + 5;

struct tdata {
    int cnt, lazy;
};

int N, Q, arr[MAX_N];
tdata st[4 * MAX_N];

void build(int node, int start, int end) {
    if (start == end) {
        st[node].cnt = arr[start];
        st[node].lazy = 0;
    }
    else {
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        st[node].cnt = st[2 * node].cnt + st[2 * node + 1].cnt;
    }
}

void update(int node, int start, int end, int l, int r) { // toggle all members in [l, r]
    // always do propagation at the start
    if (st[node].lazy) {
        st[node].cnt = (end - start + 1) - st[node].cnt;
        if (start != end) {
            st[2 * node].lazy = !st[2 * node].lazy;
            st[2 * node + 1].lazy = !st[2 * node + 1].lazy;
        }
        st[node].lazy = 0;
    }

    if (r < start || end < l) return;
    if (l <= start && end <= r) {
        st[node].cnt = (end - start + 1) - st[node].cnt;
        if (start != end) {
            st[2 * node].lazy = !st[2 * node].lazy;
            st[2 * node + 1].lazy = !st[2 * node + 1].lazy;
        }
    }
    else {
        int mid = (start + end) / 2;
        update(2 * node, start, mid, l, r);
        update(2 * node + 1, mid + 1, end, l, r);
        st[node].cnt = st[2 * node].cnt + st[2 * node + 1].cnt;
    }
}

int query(int node, int start, int end, int l, int r) {
    // always do propagation at the start
    if (st[node].lazy) {
        st[node].cnt = (end - start + 1) - st[node].cnt;
        if (start != end) {
            st[2 * node].lazy = !st[2 * node].lazy;
            st[2 * node + 1].lazy = !st[2 * node + 1].lazy;
        }
        st[node].lazy = 0;
    }

    if (r < start || end < l) return 0;
    if (l <= start && end <= r) return st[node].cnt;
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
            int l, r; cin >> l >> r;
            update(1, 1, N, l, r);
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

    solve();
}
