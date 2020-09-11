// Descending on segment tree
// Problem link: https://cses.fi/problemset/task/1143/

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 2e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

int n, q;
int arr[MAX_N], st[4 * MAX_N];
 
void build(int node, int start, int end) {
    if (start == end)
        st[node] = arr[start];
    else {
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        st[node] = max(st[2 * node], st[2 * node + 1]);
    }
}
 
void update(int node, int start, int end, int idx, int val) {
    if (start == end) {
        arr[idx] += val;
        st[node] += val;
    }
    else {
        int mid = (start + end) / 2;
        if (idx <= mid) update(2 * node, start, mid, idx, val);
        else update(2 * node + 1, mid + 1, end, idx, val);
        st[node] = max(st[2 * node], st[2 * node + 1]);
    }
}
 
int query(int node, int start, int end, int val) {
    if (start == end) return (st[node] >= val) ? start : 0;
    int mid = (start + end) / 2;
    if (st[2 * node] >= val) 
        return query(2 * node, start, mid, val);
    else 
        return query(2 * node + 1, mid + 1, end, val);
}
 
void solve() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> arr[i];
    build(1, 1, n);
    while (q--) {
        int val; cin >> val;
        int idx = query(1, 1, n, val);
        cout << idx << " ";
        if (idx) update(1, 1, n, idx, -val);
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