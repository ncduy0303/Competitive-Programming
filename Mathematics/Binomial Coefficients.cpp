// Quick calculation of nCk
// Time complexity: O(1) per query, O(n) precomputation
// Precompute all the factorials and modular inverse to calculate nCk = n!/(k!(n-k)!)
// Problem link: https://cses.fi/problemset/task/1079

#include <bits/stdc++.h>
 
using namespace std;
 
#define ar array
#define ll long long
 
const int MAX_N = 1e5 + 5;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;

ll qexp(ll a, ll b, ll m) {
    ll res = 1;
    while (b) {
        if (b % 2) res = res * a % m;
        a = a * a % m;
        b /= 2;
    }
    return res;
}

vector<ll> fact, invf;

void precompute(int n) {
    fact.assign(n + 1, 1); 
    for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i % MOD;
    invf.assign(n + 1, 1);
    invf[n] = qexp(fact[n], MOD - 2, MOD);
    for (int i = n - 1; i > 0; i--) invf[i] = invf[i + 1] * (i + 1) % MOD;
}

ll nCk(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] * invf[k] % MOD * invf[n - k] % MOD;
    // return fact[n] * qexp(fact[k], MOD - 2, MOD) % MOD * qexp(fact[n - k], MOD - 2, MOD) % MOD;
}

// A trick to calculate large factorial without overflowing is to take log at every step when precompute and take exponential when calculating
// Don't need invf[] now because it is the same as negative log of fact
vector<double> log_fact;
void precompute_log(int n) {
    log_fact.assign(n + 1, 0.0);
    log_fact[0] = 0.0; 
    for (int i = 1; i <= n; i++) log_fact[i] = log_fact[i - 1] + log(i); 
}

ll log_nCk(int n, int k) { 
    if (k < 0 || k > n) return 0;
    return exp(log_fact[n] - log_fact[n - k] - log_fact[k]); 
}

void solve() {
    int n, k; cin >> n >> k;
    cout << nCk(n, k) << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    precompute(1e6);
    int tc = 1;
    cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t << ": ";
        solve();
    }
}
