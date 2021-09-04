// Quick calculation of (a^b) mod m
// Time complexity: O(logb)

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 5;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;

// Recursive
ll qexp(ll a, ll b, ll m) {
    if (b == 0) return 1;
    ll res = qexp(a, b / 2, m);
    res = res * res % m;
    if (b % 2) res = res * a % m;
    return res;
}

// Iterative (slightly faster)
ll qexp(ll a, ll b, ll m) {
    ll res = 1;
    while (b) {
        if (b % 2) res = res * a % m;
        a = a * a % m;
        b /= 2;
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
    int tc = 1;
    // cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t << ": ";
        solve();
    }
}