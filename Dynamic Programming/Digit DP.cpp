// Digit DP
// Problem: find the sum of the digits of the numbers between a and b (0 <= a <= b <= 1e9)
// Link: https://www.spoj.com/problems/CPCRC1C/

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 5;
const int MOD = 1e9 + 7;

typedef long long ll;

int a, b;
vector<int> num;
ll dp[10][9 * 10][2];
// dp[pos][sum][flag]
// pos = current position, starting from the left (0-index)
// sum = sum of all digits till the given position
// flag = the number we are building has already become smaller than b? [0 = no, 1 = yes]

ll memo(int pos, int sum, int flag) {
    if (pos == num.size()) return sum; // finish the string
    if (dp[pos][sum][flag] != -1) return dp[pos][sum][flag];

    ll res = 0;
    int lmt = (flag) ? 9 : num[pos];
    for (int i = 0; i <= lmt; i++) {
        int next_flag = (i < lmt) ? 1 : flag;
        res += memo(pos + 1, sum + i, next_flag);
    }
    return dp[pos][sum][flag] = res;
}

ll solve(int n) {
    num.clear();
    while (n) {
        num.push_back(n % 10);
        n /= 10;
    }
    reverse(num.begin(), num.end());
    memset(dp, -1, sizeof dp);
    return memo(0, 0, 0);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> a >> b;
    while (a != -1 && b != -1) {
        cout << solve(b) - solve(a - 1) << "\n";
        cin >> a >> b;
    }
}

