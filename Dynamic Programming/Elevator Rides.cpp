// Problem: Elevator Rides
// Link: https://cses.fi/problemset/task/1653
// Idea: DP with bitmask
// Time complexity: O(2^n * n), better than naive approach (n! * n)

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 20;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int n, x; cin >> n >> x;
    int weight[n]; for (int i = 0; i < n; i++) cin >> weight[i];

    pair<int, int> dp[1 << n];
    // for each subset i, dp[i].first is the minimum number of rides, dp[i].second is the minimum weight of the last ride
    // be careful that if dp[i].second > 0, then the answer is dp[i].first + 1;
    dp[0] = {0, 0}; // base case (empty subset)
    for (int i = 1; i < (1 << n); i++) {
        // initially, upper bound is n + 1 rides
        dp[i] = {n + 1, 0};
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                auto cur = dp[i ^ (1 << j)];
                if (cur.second + weight[j] <= x) { // add j to the current ride
                    cur.second += weight[j];
                }
                else { // reserves a new ride for j
                    cur.first++;
                    cur.second = weight[j];
                }
                dp[i] = min(dp[i], cur);
            }
        }
    }
    cout << dp[(1 << n) - 1].first + (dp[(1 << n) - 1].second > 0);
}
