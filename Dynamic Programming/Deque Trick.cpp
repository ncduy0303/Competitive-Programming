// Optimise from O(NK^2) to O(NK) by answering min/max queries among k consecutive elements in O(1) in DP transition
// Problem link: https://codeforces.com/contest/1077/problem/F2

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;



void solve() {
    int n, k, x; cin >> n >> k >> x;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    ll dp[n + 1][x + 1]; // dp[i][j] = answer using j pictures from the first i-th pictures
    memset(dp, -0x3f, sizeof dp);
    dp[0][0] = 0;
    for (int j = 1; j <= x; j++) {
        deque<ar<ll,2>> dq; // {id, value}
        dq.push_back({j - 1, dp[j - 1][j - 1]});
        for (int i = j; i <= n; i++) {
            while (dq.size() && dq.front()[0] < i - k) dq.pop_front();
            dp[i][j] = dq.front()[1] + a[i];
            while (dq.size() && dp[i][j - 1] >= dq.back()[1]) dq.pop_back();
            dq.push_back({i, dp[i][j - 1]});
        }

    }
    ll ans = -1;
    for (int i = 0; i < k; i++) ans = max(ans, dp[n - i][x]);
    cout << ans << "\n";
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