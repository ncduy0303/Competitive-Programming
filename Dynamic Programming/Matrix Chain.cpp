// Similar to "Cutting Sticks", a variation of Matrix Chain Multiplication DP Problem
// Time complexity: O(n^3)
// Problem link: https://www.spoj.com/problems/MIXTURES/

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;



void solve() {
    int n;
    while(cin >> n) {
        int arr[n][n];
        for (int i = 0; i < n; i++) cin >> arr[i][i];
        int dp[n][n];
        // diagonal dp (another way to achieve the same thing as range dp)
        for (int l = 0; l < n; l++) {
            for (int i = 0, j = i + l; j < n; i++, j++) {
                if (l == 0) dp[i][j] = 0;
                else {
                    dp[i][j] = INF;
                    for (int k = i; k < j; k++) {
                        if (dp[i][j] > dp[i][k] + dp[k + 1][j] + arr[i][k] * arr[k + 1][j]) {
                            dp[i][j] = dp[i][k] + dp[k + 1][j] + arr[i][k] * arr[k + 1][j];
                            arr[i][j] = (arr[i][k] + arr[k + 1][j]) % 100;
                        }
                    }
                }
            }
        }
        cout << dp[0][n - 1] << "\n";
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