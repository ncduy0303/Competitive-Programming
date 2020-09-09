// Given 2 strings x and y of length n and m, find the the longest common subsequence (LCS)
// Time complexity: O(nm)
// Problem link: https://dunjudge.me/analysis/problems/171/

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;



void solve() {
    string x, y; cin >> x >> y;
    int n = x.size(), m = y.size();
    int dp[n + 1][m + 1] = {};
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (x[i - 1] == y[j - 1]) 
                dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
            else
                dp[i][j] = max({dp[i][j], dp[i - 1][j], dp[i][j - 1]});
        }
    }
    cout << dp[n][m];
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