// Find the sum of the digits of the numbers between a and b (0 <= a <= b <= 1e9)
// Problem link: https://www.spoj.com/problems/CPCRC1C/

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

vector<int> num;
ll dp[10][9 * 10][2];

// dp[pos][sum][flag]
// pos = current position, starting from the left (0-index)
// sum = sum of all digits till the given position
// flag = the number we are building has already become smaller than b? [0 = no, 1 = yes]

ll memo(int pos, int sum, int flag) {
    if (pos == num.size()) return sum;
    if (dp[pos][sum][flag] != -1) return dp[pos][sum][flag];

    ll res = 0;
    int lmt = (flag) ? 9 : num[pos];
    for (int i = 0; i <= lmt; i++) {
        int next_flag = (i < lmt) ? 1 : flag;
        res += memo(pos + 1, sum + i, next_flag);
    }
    return dp[pos][sum][flag] = res;
}

ll calc(int n) {
    num.clear();
    while (n) {
        num.push_back(n % 10);
        n /= 10;
    }
    reverse(num.begin(), num.end());
    memset(dp, -1, sizeof dp);
    return memo(0, 0, 0);
}

void solve() {
    while (true) {
        int a, b; cin >> a >> b;
        if (a == -1 && b == -1) return;
        cout << calc(b) - calc(a - 1) << "\n";
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