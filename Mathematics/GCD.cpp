// Find the greatest common divisor (GCD) of two integers
// Time complexity: O(log(min(a, b)))

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 5;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

// extended version to find x, y such that ax + by = gcd(a, b)
ll gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {x = 1, y = 0; return a;}
    ll x1, y1, d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

// find a solution of a Linear Diophantine Equation
bool lde(ll a, ll b, ll c, ll &x, ll &y) {
    ll d = gcd(abs(a), abs(b), x, y);
    if (c % d) return false; 
    x *= c / d; 
    y *= c / d;
    if (a < 0) x = -x;
    if (b < 0) y = -y;
    return true;
}

void shift(ll a, ll b, ll &x, ll &y, ll cnt) {
    x += cnt * b;
    y -= cnt * a;
}

ll inv_mod(ll a, ll m) {
    ll x, y;
    gcd(a, m, x, y);
    return (m + x % m) % m;
}

// solve ax = b (mod m)
ll lce(ll a, ll b, ll m) {
    ll d = gcd(a, m);
    if (d != 1) {
        if (b % d) return -1;
        a /= d; b /= d; m /= d;
    }
    return b * inv_mod(a, m) % m;
}

void solve() {
    int a, b; cin >> a >> b;
    cout << gcd(a, b) << "\n";

    // using C++ inbuilt function
    // cout << __gcd(a, b) << "\n";
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