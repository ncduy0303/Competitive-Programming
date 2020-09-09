// Quick calculation of (a^b) mod m
// Time complexity: O(logb)
// Problem link: https://dunjudge.me/analysis/problems/53/

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

// Recursive
ll qexp(ll a, ll b, ll m) {
    if (b == 0) return 1;
    ll res = qexp(a, b/2, m);
    res = res * res % m;
    if (b & 1) res = res * a % m;
    return res;
}

// Iterative (slightly faster)
ll qexp(ll a, ll b, ll m) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

void solve() {
    int a, b, m; cin >> a >> b >> m;
    cout << qexp(a, b, m) << "\n";
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