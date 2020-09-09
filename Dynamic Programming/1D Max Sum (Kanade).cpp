// Given an array of integers, find the maximum sum subarray
// Time complexity: O(n)
// Problem link: https://cses.fi/problemset/task/1643

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;



void solve() {
    int n; cin >> n;
    // set to -LINF to return non-empty maximum subarray sum, otherwise set to 0
    ll ans = -LINF, cur = -LINF; 
    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        cur = max(x, cur + x);
        // cur = max(0, cur + x);
        ans = max(ans, cur);
    }
    cout << ans << "\n";
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