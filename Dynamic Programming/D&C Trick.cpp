// Use Divide & Conquer (D&C) to optimize a DP solution
// Problem link: https://www.spoj.com/problems/LARMY/

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 5e3 + 1;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;

int n, m, a[MAX_N];
int ps[MAX_N][MAX_N], dp[MAX_N][MAX_N];
// dp[i][j] = minimum unhappiness when splitting the first j-th people into i rows

int cost(int i, int j) {
    return ps[j][j] - ps[i - 1][j] - ps[j][i - 1] + ps[i - 1][i - 1];
}

void dac(int i, int l, int r, int ql, int qr) {
    if (l > r) return;
    int mid = (l + r) / 2;
    ar<int,2> res = {INF, INF};
    for (int k = ql; k <= min(mid, qr); k++) {
        res = min(res, {dp[i - 1][k - 1] + cost(k, mid), k});
    }
    dp[i][mid] = res[0];
    dac(i, l, mid - 1, ql, res[1]);
    dac(i, mid + 1, r, res[1], qr);
}

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {  
        for (int j = 1; j < i; j++) {
            ps[i][j] = a[j] > a[i];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            ps[i][j] = ps[i - 1][j] + ps[i][j - 1] - ps[i - 1][j - 1] + ps[i][j];
        }
    }
    memset(dp, 0x3f, sizeof dp);
    dp[0][0] = 0;

    // Naive O(mn^2) by directly applying dp[i][j] = min{dp[i - 1][k - 1] + cost(k, j)} for 1 <= k <= j
    // for (int i = 1; i <= m; i++) {
    //     for (int j = 1; j <= n; j++) {
    //         for (int k = 1; k <= j; k++) {
    //             dp[i][j] = min(dp[i][j], dp[i - 1][k - 1] + cost(k, j));
    //         }
    //     }
    // }
    
    // Optimised O(mnlogn) using D&C
    for (int i = 1; i <= m; i++) dac(i, i, n, i, n);

    cout << dp[m][n] << "\n";
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