// Lazy Propagation
// range_add_update (using the addval value)
// range_set_update (using the setval and lazyset value)
// range_sum_of_squares_query
// Problem link: https://www.spoj.com/problems/SEGSQRSS/
// Idea: notice that we also need to store the normal sum to be able to update (a + x)^2 = a^2 + x^2 + 2ax

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 1e5 + 5;

struct tdata {
    ll sum, sum_square;
    ll setval, addval;
    bool lazyset;
};

int N, Q, arr[MAX_N];
tdata st[4 * MAX_N];

void build(int node, int start, int end) {
    if (start == end) {
        st[node].sum = arr[start];
        st[node].sum_square = arr[start] * arr[start];
        st[node].addval = 0;
        st[node].setval = 0;
    }
    else {
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        st[node].sum = st[2 * node].sum + st[2 * node + 1].sum;
        st[node].sum_square = st[2 * node].sum_square + st[2 * node + 1].sum_square;
    }
}

void down(int node, int start, int end) { // a separate function for lazy propagation to avoid complexity
    int mid = (start + end) / 2;
    if (st[node].addval) {
        ll val = st[node].addval;
        st[2 * node].addval += val;
        st[2 * node + 1].addval += val;
        st[2 * node].sum_square += val * val * (mid - start + 1) + 2 * val * st[2 * node].sum;
        st[2 * node + 1].sum_square += val * val * (end - mid) + 2 * val * st[2 * node + 1].sum;
        st[2 * node].sum += val * (mid - start + 1);
        st[2 * node + 1].sum += val * (end - mid);
        st[node].addval = 0;
    }
    if (st[node].lazyset) {
        ll val = st[node].setval;
        st[2 * node].addval = 0;
        st[2 * node + 1].addval = 0;
        st[2 * node].setval = val;
        st[2 * node + 1].setval = val;
        st[2 * node].sum_square = val * val * (mid - start + 1);
        st[2 * node + 1].sum_square = val * val * (end - mid);
        st[2 * node].sum = val * (mid - start + 1);
        st[2 * node + 1].sum = val * (end - mid);
        st[2 * node].lazyset = 1;
        st[2 * node + 1].lazyset = 1;
        st[node].lazyset = 0;
    }
}

void add_update(int node, int start, int end, int l, int r, ll val) { // add all members in [l, r] by val
    if (r < start || end < l) return;
    if (l <= start && end <= r) {
        st[node].sum_square += val * val * (end - start + 1) + 2 * val * st[node].sum;
        st[node].sum += val * (end - start + 1);
        st[node].addval += val;
    }
    else {
        down(node, start, end);
        int mid = (start + end) / 2;
        add_update(2 * node, start, mid, l, r, val);
        add_update(2 * node + 1, mid + 1, end, l, r, val);
        st[node].sum = st[2 * node].sum + st[2 * node + 1].sum;
        st[node].sum_square = st[2 * node].sum_square + st[2 * node + 1].sum_square;
    }
}

void set_update(int node, int start, int end, int l, int r, ll val) { // set all members in [l, r] to val
    if (r < start || end < l) return;
    if (l <= start && end <= r) {
        st[node].sum_square = val * val * (end - start + 1);
        st[node].sum = val * (end - start + 1);
        st[node].addval = 0;
        st[node].setval = val;
        st[node].lazyset = 1;
    }
    else {
        down(node, start, end);
        int mid = (start + end) / 2;
        set_update(2 * node, start, mid, l, r, val);
        set_update(2 * node + 1, mid + 1, end, l, r, val);
        st[node].sum = st[2 * node].sum + st[2 * node + 1].sum;
        st[node].sum_square = st[2 * node].sum_square + st[2 * node + 1].sum_square;
    }
}

ll query(int node, int start, int end, int l, int r) {
    if (r < start || end < l) return 0;
    if (l <= start && end <= r) return st[node].sum_square;
    else {
        down(node, start, end);
        int mid = (start + end) / 2;
        return query(2 * node, start, mid, l, r) + query(2 * node + 1, mid + 1, end, l, r);
    }
}

void solve() {
    memset(st, 0, sizeof st);
    cin >> N >> Q;
    for (int i = 1; i <= N; i++) cin >> arr[i];
    build(1, 1, N);
    while (Q--) {
        char c; cin >> c;
        if (c == '0') {
            int l, r; ll val; cin >> l >> r >> val;
            set_update(1, 1, N, l, r, val);
        }
        else if (c == '1') {
            int l, r; ll val; cin >> l >> r >> val;
            add_update(1, 1, N, l, r, val);
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
    for (int i = 1; i <= tc; i++) {
        cout << "Case " << i << ":\n";
        solve();
    }
}
