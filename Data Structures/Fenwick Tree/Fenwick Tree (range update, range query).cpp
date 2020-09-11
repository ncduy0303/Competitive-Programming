// Use 2 fenwick trees to support both range updates and range queries (RURQ)
// A combination of PURQ and RUPQ
// Problem link: https://www.spoj.com/problems/HORRIBLE/

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

#define LSOne(S) ((S) & (-S))

int n, q;
ll ft1[MAX_N], ft2[MAX_N];

void update(ll *ft, int x, ll v) {
    for (; x <= n; x += LSOne(x))
        ft[x] += v;
}

void range_update(int l, int r, ll v) {
    update(ft1, l, v);
    update(ft1, r + 1, -v);
    update(ft2, l, v * (l - 1));
    update(ft2, r + 1, -v * r);
}

ll sum(ll *ft, int x) {
    ll res = 0;
    for (; x; x -= LSOne(x)) 
        res += ft[x];
    return res;
}

// sum of all elements in [1...x]
ll ps(int x) {
    return sum(ft1, x) * x - sum(ft2, x);
}

ll rsq(int l, int r) { 
    return ps(r) - ps(l - 1);
}

void solve() {
    memset(ft1, 0, sizeof ft1);
    memset(ft2, 0, sizeof ft2);
    cin >> n >> q;
    while (q--) {
        int t, l, r; cin >> t >> l >> r;
        if (t == 0) {
            int v; cin >> v;
            range_update(l, r, v);
        }
        else {
            cout << rsq(l, r) << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int tc; cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t  << ": ";
        solve();
    }
}