// Sum-over-subset dp to optimise from O(4^n) or O(3^n) to O(n*2^n) 
// Problem link: https://cses.fi/problemset/task/1654

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MAX_M = 20;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;

int inv(int x) {return x ^ ((1 << MAX_M) - 1);}

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    vector<int> dp(1 << MAX_M), dp_inv(1 << MAX_M);
    for (int &x : a) {
        cin >> x;
        dp[x]++;
        dp_inv[inv(x)]++;
    }
    for (int i = 0; i < MAX_M; i++) {
        for (int mask = 0; mask < (1 << MAX_M); mask++) {
            if (mask & (1 << i)) {
                dp[mask] += dp[mask ^ (1 << i)];
                dp_inv[mask] += dp_inv[mask ^ (1 << i)];
            }
        }
    }
    for (int x : a) {
        cout << dp[x] << " " << dp_inv[inv(x)] << " " << n - dp[inv(x)] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int tc = 1;
    // cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t  << ": ";
        solve();
    }
}