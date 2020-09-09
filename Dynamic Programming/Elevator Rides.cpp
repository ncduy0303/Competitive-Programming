// Find the minimum of elevator rides to move n people knowing everyone's weight and the elevator's limit
// Time complexity: O(2^n * n)
// Problem link: https://cses.fi/problemset/task/1653
// Use DP with bitmask

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;



void solve() {
    int n, x; cin >> n >> x;
    int weight[n]; 
    for (int i = 0; i < n; i++) cin >> weight[i];

    ar<int,2> dp[1 << n];
    // dp[i][0] = the minimum number of rides for bitmask i
    // dp[i][1] = the minimum weight of the last ride for bitmask i
    dp[0] = {0, 0};
    for (int i = 1; i < (1 << n); i++) {
        // upper bound is n + 1 rides
        dp[i] = {n + 1, 0};
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                auto cur = dp[i ^ (1 << j)];
                if (cur[1] + weight[j] <= x) { // add j to the current ride
                    cur[1] += weight[j];
                }
                else { // reserves a new ride for j
                    cur[0]++;
                    cur[1] = weight[j];
                }
                dp[i] = min(dp[i], cur);
            }
        }
    }
    // if dp[i].second > 0, then the answer is dp[i].first + 1
    cout << dp[(1 << n) - 1][0] + (dp[(1 << n) - 1][1] > 0);
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