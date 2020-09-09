// Given a list of jobs with start time, end time, and profit, find the maximum profit
// Time complexity: O(nlogn)
// Problem link: https://dunjudge.me/analysis/problems/414/

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
    ar<ll,3> arr[n];
    for (int i = 0; i < n; i++) cin >> arr[i][1] >> arr[i][0] >> arr[i][2];
    sort(arr, arr + n); // sort based on end time
    ll dp[n];
    dp[0] = arr[0][2];
    for (int i = 1; i < n; i++) {
        int k = lower_bound(arr, arr + n, ar<ll,3>{arr[i][1], 0, 0}) - arr - 1;
        if (k >= 0)
            dp[i] = max(dp[i - 1], dp[k] + arr[i][2]);
        else
            dp[i] = max(dp[i - 1], arr[i][2]);
 
    }
    cout << dp[n - 1] << "\n";
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