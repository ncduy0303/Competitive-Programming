// Problem link: https://cses.fi/problemset/task/1651

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 2e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

#define LSOne(S) ((S) & (-S))

int n, q;
ll ft[MAX_N];
 
void update(int x, int v) {
    for (; x <= n; x += LSOne(x)) 
        ft[x] += v;
}

void range_update(int l, int r, int v) {
    update(l, v);
    update(r + 1, -v);
}
 
ll sum(int x) {
    ll res = 0;
    for (; x; x -= LSOne(x)) 
        res += ft[x];
    return res;
}

void solve() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        range_update(i, i, x);
    }
    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int l, r, v; cin >> l >> r >> v;
            range_update(l, r, v);
        }
        else {
            int x; cin >> x;
            cout << sum(x) << "\n";
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