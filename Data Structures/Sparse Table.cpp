// Answer range query for static array
// Time complexity: O(nlogn) construction, O(logn) query
// Can be modified to be O(1) query for some queries (i.e minimum/maximum, gcd)
// Problem link: https://cses.fi/problemset/task/1647/, https://cses.fi/problemset/task/1650

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 2e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

const int MAX_L = 18;

int n, q;
int arr[MAX_N], dp[MAX_N][MAX_L];
 
void build_sparse_table() {
    for (int i = 1; i <= n; i++)
        dp[i][0] = arr[i];
    for (int j = 1; j < MAX_L; j++)
        for (int i = 1; i + (1 << j) <= n + 1; i++)
            dp[i][j] = min(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
            // dp[i][j] = dp[i][j - 1] ^ dp[i + (1 << (j - 1))][j - 1];
}

int lg(int x) {
    return 32 - __builtin_clz(x) - 1;
}

int min_query(int l, int r) { // O(1)
    int k = lg(r - l + 1);
    return min(dp[l][k], dp[r - (1 << k) + 1][k]);
}

int xor_query(int l, int r) { // O(logn)
    int k = r - l + 1, ans = 0;
    for (int i = 0; i < MAX_L; i++) {
        if (k & (1 << i)) {
            ans ^= dp[l][i];
            l += (1 << i);
        }
    }
    return ans;
}

void solve() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> arr[i];
    build_sparse_table();
    while (q--) {
        int l, r; cin >> l >> r;
        cout << min_query(l, r) << "\n";
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
