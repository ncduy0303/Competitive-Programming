// Generate the all primes <= n
// Time complexity: O(nlog(logn))
// Problem link: https://dunjudge.me/analysis/problems/271/

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

// Check if n is a prime in O(sqrt(n))
bool prime_check(int n) { 
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0)
            return false;
    return true;
}

// Generate the all primes <= n in O(nlog(logn))
vector<int> sieve(int n) {
    vector<int> primes, is_prime(n + 1, 1);
    for (int i = 2; i * i <= n; i++)
        if (is_prime[i])
            for (int j = i + i; j <= n; j += i)
                is_prime[j] = 0;
    for (int i = 2; i <= n; i++)
        if (is_prime[i])
            primes.push_back(i);
    return primes;
}

// Modified sieve to make enable prime factorization in log(n)
// Instead of just storing whether a number is prime, we will store its smallest prime factor greater than 1
vector<int> spf;

vector<int> modified_sieve(int n) {
    for (int i = 1; i <= n; i++)
        spf[i] = i;
    vector<int> primes;
    for (int i = 2; i * i <= n; i++) 
        if (spf[i] == i)
            for (int j = i + i; j <= n; j += i)
                if (spf[j] == j)
                    spf[j] = i;
    for (int i = 2; i <= n; i++)
        if (spf[i] == i)
            primes.push_back(i);
    return primes;
}

vector<int> factorize(int x) {
    vector<int> res;
    while (x > 1) {
        res.push_back(spf[x]);
        x /= spf[x];
    }
    return res;
}

void solve() { 
    // print the n-th prime (n <= 1e4)
    // note that the 10000-th prime is 104729
    const int mx = 104729;
    spf.resize(mx + 1);
    vector<int> primes = modified_sieve(104729);
    int n; cin >> n;
    cout << primes[n - 1] << "\n";
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
