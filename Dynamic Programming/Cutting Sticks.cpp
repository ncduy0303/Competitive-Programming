// Given a length x and n cutting points, find the minimum cost perform all n cuts
// Cost of a cut is equal to the length of the current stick
// A variation of Matrix Chain Multiplication DP Problem
// Time complexity: O(n^3), can be reduced to O(n^2) with Knuth Optimization
// Problem link: https://vjudge.net/problem/UVA-10003

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 50 + 5;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

int opt[MAX_N][MAX_N];

void solve() {
    while (true) {
        int x; cin >> x;
        if (!x) return;

        int n; cin >> n;
        int arr[n + 2];
        // adding the beginning point and the ending point
        arr[0] = 0; arr[n + 1] = x;
        for (int i = 1; i <= n; i++) cin >> arr[i];
        vector<vector<int>> dp(n + 2, vector<int>(n + 2, INF));
        for (int i = 0; i < n + 1; i++) {
            dp[i][i + 1] = 0;
            opt[i][i + 1] = i;
        }
        // range dp
        for (int i = n + 1; i >= 0; i--) {
            for (int j = i; j <= n + 1; j++) {
                for (int k = i + 1; k < j; k++) {
                    if (dp[i][j] > dp[i][k] + dp[k][j] + arr[j] - arr[i]) {
                        dp[i][j] = dp[i][k] + dp[k][j] + arr[j] - arr[i];
                    }
                }
                // Knuth Optimization (only need to change 2 lines)
                // Condition: dp[i][j] = min{i < k < j}(dp[i][k] + dp[k][j]) + C[i][j]
                // for (int k = opt[i][j - 1]; k <= opt[i + 1][j]; k++) {
                //     if (dp[i][j] > dp[i][k] + dp[k][j] + arr[j] - arr[i]) {
                //         dp[i][j] = dp[i][k] + dp[k][j] + arr[j] - arr[i];
                //         opt[i][j] = k;
                //     }
                // }
            }
        }
        cout << "The minimum cutting is " << dp[0][n + 1] << ".\n"; 
    }
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