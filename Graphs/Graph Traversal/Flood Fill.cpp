// Problem link: https://cses.fi/problemset/task/1192

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e3 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;
 
int n, m, visited[MAX_N][MAX_N];
char grid[MAX_N][MAX_N];
 
const int di[] = {1, 0, -1, 0};
const int dj[] = {0, -1, 0, 1};
 
bool valid(int i, int j) {
    return i >= 0 && j >= 0 && i < n && j < m && grid[i][j] == '.';
}
 
void dfs(int i, int j) {
    visited[i][j] = 1;
    for (int k = 0; k < 4; k++) {
        int ni = i + di[k], nj = j + dj[k];
        if (valid(ni, nj) && !visited[ni][nj]) {
            dfs(ni, nj);
        }
    }
}
 
void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < m; j++)
            cin >> grid[i][j];
    
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (valid(i, j) && !visited[i][j]) {
                dfs(i, j);
                ans++;
            }
        }
    }
    cout << ans << "\n";
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