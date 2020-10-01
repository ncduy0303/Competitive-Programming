// Quick calculation of nCk
// Time complexity: O(1) per query, O(n) precomputation
// Precompute all the factorials and modular inverse to calculate nCk = n!/(k!(n-k)!)
// Problem link: https://cses.fi/problemset/task/1079

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e6 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

ll qexp(ll a, ll b, ll m) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

ll fact[MAX_N], invf[MAX_N];

void precompute() {
    fact[0] = invf[0] = 1;
    for (int i = 1; i < MAX_N; i++) {
        fact[i] = fact[i - 1] * i % MOD;
        invf[i] = qexp(fact[i], MOD - 2, MOD); // Fermat's little theorem
    }
}

ll nCk(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] * invf[k] % MOD * invf[n - k] % MOD;

    // if there are only a few queries, then don't need to precompute invf[] => faster
    // return fact[n] * qexp(fact[k], MOD - 2, MOD) % MOD * qexp(fact[n - k], MOD - 2, MOD) % MOD;
}

// A trick to calculate large factorial without overflowing is to take log at every step when precompute and take exponential when calculating
// Don't need invf[] now because it is the same as negative log of fact
double log_fact[MAX_N];
void precompute_log() {
    log_fact[0] = 0.0; 
    for (int i = 1; i < MAX_N; i++)
        log_fact[i] = log_fact[i - 1] + log(i); 
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
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int tc; cin >> tc;
    precompute();
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t  << ": ";
        solve();
    }
}
