// Problem link: https://cses.fi/problemset/task/1648

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
 
ll sum(int x) {
    ll res = 0;
    for (; x; x -= LSOne(x)) 
        res += ft[x];
    return res;
}
 
ll rsq(int l, int r) {
    return sum(r) - sum(l - 1);
}

void solve() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        update(i, x);
    }
    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int x, v; cin >> x >> v;
            update(x, v - rsq(x, x));
        }
        else {
            int l, r; cin >> l >> r;
            cout << rsq(l, r) << "\n";
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