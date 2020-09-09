// Count the number of ways to place the queens so that no two queens are attacking each other
// Use backtracking
// Problem link: https://cses.fi/problemset/task/1624/

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

const int n = 8;

int r[n], c[n], d1[2 * n], d2[2 * n], blocked[n][n], ans;
 
void place(int j) {
    if (j == n) {
        ans++;
        return;
    }
    if (c[j]) place(j + 1);
    else {
        for (int i = 0; i < n; i++) {
            if (!blocked[i][j] && !r[i] && !d1[i + j] && !d2[i - j + n]) {
                blocked[i][j] = r[i] = d1[i + j] = d2[i - j + n] = 1;
                place(j + 1);
                blocked[i][j] = r[i] = d1[i + j] = d2[i - j + n] = 0;
            }
        }
    }
}
 
void solve() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char x; cin >> x;
            if (x == '*') blocked[i][j] = 1;
        }
    }
    place(0);
    cout << ans;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "i", stdin);
    // freopen("output.txt", "w", stdout);

    int tc; tc = 1;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t  << ": ";
        solve();
    }
}