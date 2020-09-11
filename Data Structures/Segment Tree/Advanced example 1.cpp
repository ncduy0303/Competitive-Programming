// Segment tree for subarray sum query
// Problem link: https://cses.fi/problemset/task/1190

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 2e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

struct tdata {
    ll sum, pref, suff, ans;
    tdata() {
        sum = pref = suff = ans = 0;
    }
    tdata(int val) {
        sum = val;
        pref = suff = ans = max(0, val);
    }
    tdata(tdata l, tdata r) {
        sum = l.sum + r.sum;
        pref = max(l.pref, l.sum + r.pref);
        suff = max(r.suff, r.sum + l.suff);
        ans = max({l.ans, r.ans, l.suff + r.pref});
    }
};
 
int n, q, arr[MAX_N];
tdata st[4 * MAX_N];
 
void build(int node, int start, int end) {
    if (start == end) {
        st[node] = tdata(arr[start]);
        return;
    }
    int mid = (start + end) / 2;
    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);
    st[node] = tdata(st[2 * node], st[2 * node + 1]);
}
 
void update(int node, int start, int end, int idx, int val) {
    if (start == end) {
        arr[idx] = val;
        st[node] = tdata(val);
        return;
    }
    int mid = (start + end) / 2;
    if (idx <= mid) update(2 * node, start, mid, idx, val);
    else update(2 * node + 1, mid + 1, end, idx, val);
    st[node] = tdata(st[2 * node], st[2 * node + 1]);
}
 
tdata query(int node, int start, int end, int l, int r) {
    if (start > r || end < l) return tdata(0);
    if (l <= start && end <= r) return st[node];
    int mid = (start + end) / 2;
    return tdata(query(2 * node, start, mid, l, r), query(2 * node + 1, mid + 1, end, l, r));
}
 
void solve() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> arr[i];
    build(1, 1, n);
    while (q--) {
        int k, x; cin >> k >> x;
        update(1, 1, n, k, x);
        cout << query(1, 1, n, 1, n).ans << "\n";
        // this is the same as 
        // cout << st[1].ans << "\n";
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