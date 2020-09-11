// Segment tree for range minimum query, point set update
// Problem link: https://cses.fi/problemset/task/1649

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 2e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

int n, q, arr[MAX_N], st[4 * MAX_N];
 
void build(int node, int start, int end) {
    if (start == end) {
        st[node] = arr[start];
        return;
    }
    int mid = (start + end) / 2;
    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);
    st[node] = min(st[2 * node], st[2 * node + 1]);
}
 
void update(int node, int start, int end, int idx, int val) {
    if (start == end) {
        arr[idx] = val;
        st[node] = val;
        return;
    }
    int mid = (start + end) / 2;
    if (idx <= mid) update(2 * node, start, mid, idx, val);
    else update(2 * node + 1, mid + 1, end, idx, val);
    st[node] = min(st[2 * node], st[2 * node + 1]);
}

int query(int node, int start, int end, int l, int r) {
    if (start > r || end < l) return INF;
    if (l <= start && end <= r) return st[node];
    int mid = (start + end) / 2;
    return min(query(2 * node, start, mid, l, r), query(2 * node + 1, mid + 1, end, l, r)); 
}
 
void solve() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> arr[i];
    build(1, 1, n);
    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int k, u; cin >> k >> u;
            update(1, 1, n, k, u);
        }
        else {
            int l, r; cin >> l >> r;
            cout << query(1, 1, n, l, r) << "\n";
        }
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