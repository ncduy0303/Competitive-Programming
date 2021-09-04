// Generate the all primes <= n
// Time complexity: O(nlog(logn)) for standard sieve, O(n) for linear sieve
// Problem link: https://cses.fi/problemset/task/2417/ (using linear sieve to generate the mobius function)

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e6 + 5;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;

// vector<int> primes, is_prime, spf;

// void sieve(int n) {
//     primes.clear();
//     is_prime.assign(n + 1, 1);
//     spf.assign(n + 1, 0);
//     is_prime[0] = is_prime[1] = false;
//     for (ll i = 2; i <= n; i++) {
//         if (is_prime[i]) {
//             primes.push_back(i);
//             spf[i] = i;
//             for (ll j = i * i; j <= n; j += i) {
//                 is_prime[j] = false;
//                 spf[j] = i;
//             }
//         }
//     }
// }

// Linear sieve including calculating the smallest prime factor (spf), Mobius function, and Euler's totient function
vector<int> primes, is_prime, spf, mobius, phi;

void sieve(int n) {
    primes.clear();
    is_prime.assign(n + 1, 1);
    spf.assign(n + 1, 0);
    mobius.assign(n + 1, 0);
    phi.assign(n + 1, 0);
    is_prime[0] = is_prime[1] = 0;
    mobius[1] = phi[1] = 1;
    for (ll i = 2; i <= n; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            spf[i] = i;
            mobius[i] = -1;
            phi[i] = i - 1;
        }
        for (auto p : primes) {
            if (i * p > n || p > spf[i]) break;
            is_prime[i * p] = 0;
            spf[i * p] = p;
            mobius[i * p] = (spf[i] == p) ? 0 : -mobius[i];
            phi[i * p] = (spf[i] == p) ? phi[i] * p : phi[i] * phi[p];
        }
    }
}

void solve() {
    int n; cin >> n;
    vector<int> cnt(MAX_N);
    while (n--) {
        int x; cin >> x;
        cnt[x]++;
    }
    ll ans = 0;
    for (int i = 1; i < MAX_N; i++) {
        if (!mobius[i]) continue;
        ll tmp = 0;
        for (int j = i; j < MAX_N; j += i) tmp += cnt[j];
        ans += tmp * (tmp - 1) / 2 * mobius[i];
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    sieve(MAX_N);
    int tc = 1;
    // cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t << ": ";
        solve();
    }
}
