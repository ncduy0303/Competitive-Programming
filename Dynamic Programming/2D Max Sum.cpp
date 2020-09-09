// Given a 2D array of integers, find the maximum sum 2D subarray
// Performing the 1D maxsum algorithm on the columns of all O(n^2) consecutive set of rows
// Time complexity: O(n^3)
// Problem link: https://vjudge.net/problem/UVA-108

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
    ll ps[n + 1][n + 1] = {};
    // Creating a prefix sum table (horizontally)
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> ps[i][j];
            ps[i][j] += ps[i][j - 1];
        }
    }

    // 2D max sum subarray
    ll ans = 0;
    for (int l = 1; l <= n; l++) { // looping through all pairs of columns, running 1D maxsum on a column
        for (int r = l; r <= n; r++) {
            ll cur = 0;
            for (int i = 1; i <= n; i++) {
                ll x = ps[i][r] - ps[i][l - 1];
                cur = max(0ll, cur + x);
                ans = max(ans, cur);        
            }
        }
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