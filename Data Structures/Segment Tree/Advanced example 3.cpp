// Segment tree with lazy propagation for range set bit count query, range toggle update
// Problem link: https://www.spoj.com/problems/LITE/

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 2e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

struct tdata {
    int cnt, lz;
    tdata() {
        cnt = lz = 0;
    }
};
 
int n, q, arr[MAX_N];
tdata st[4 * MAX_N];
 
void down(int node, int start, int end) { 
    if (st[node].lz) {
        st[node].cnt = (end - start + 1) - st[node].cnt;
        if (start != end) {
            st[2 * node].lz = !st[2 * node].lz;
            st[2 * node + 1].lz = !st[2 * node + 1].lz;
        }
        st[node].lz = 0;
    }
}

void update(int node, int start, int end, int l, int r) { 
    down(node, start, end);
    if (r < start || end < l) return;
    if (l <= start && end <= r) {
        st[node].cnt = (end - start + 1) - st[node].cnt;
        if (start != end) {
            st[2 * node].lz = !st[2 * node].lz;
            st[2 * node + 1].lz = !st[2 * node + 1].lz;
        }
        return;
    }
    int mid = (start + end) / 2;
    update(2 * node, start, mid, l, r);
    update(2 * node + 1, mid + 1, end, l, r);
    st[node].cnt = st[2 * node].cnt + st[2 * node + 1].cnt;
}


int query(int node, int start, int end, int l, int r) {
    down(node, start, end);
    if (r < start || end < l) return 0;
    if (l <= start && end <= r) return st[node].cnt;
    int mid = (start + end) / 2;
    return query(2 * node, start, mid, l, r) + query(2 * node + 1, mid + 1, end, l, r);
}
 
void solve() {
    cin >> n >> q;
    while (q--) {
        int t, l, r; cin >> t >> l >> r;
        if (t == 0) update(1, 1, n, l, r);
        else cout << query(1, 1, n, l, r) << "\n";
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