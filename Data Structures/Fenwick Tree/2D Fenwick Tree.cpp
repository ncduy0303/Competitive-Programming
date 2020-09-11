// Problem link: https://cses.fi/problemset/task/1739

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e3 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

#define LSOne(S) ((S) & (-S))

int n, q, ft[MAX_N][MAX_N];
char grid[MAX_N][MAX_N];
 
void update(int x, int y, int v) {
    for (int tx = x; tx <= n; tx += LSOne(tx))
        for (int ty = y; ty <= n; ty += LSOne(ty))
            ft[tx][ty] += v;
}
 
int sum(int x, int y) {
    int res = 0;
    for (int tx = x; tx; tx -= LSOne(tx))
        for (int ty = y; ty; ty -= LSOne(ty))
            res += ft[tx][ty];
    return res;
}

int query(int x1, int y1, int x2, int y2) {
    return sum(x2, y2) - sum(x1 - 1, y2) - sum(x2, y1 - 1) + sum(x1 - 1, y1 - 1);
}

void solve() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == '*') update(i, j, 1);
        }
    }
    while (q--) {
        char c; cin >> c;
        if (c == '1') {
            int x, y; cin >> x >> y;
            if (grid[x][y] == '*') {
                update(x, y, -1);
                grid[x][y] = '.';
            }
            else {
                update(x, y, 1);
                grid[x][y] = '*';
            }
        }
        else {
            int x1, x2, y1, y2; cin >> x1 >> y1 >> x2 >> y2;
            cout << query(x1, y1, x2, y2) << "\n";
        }
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