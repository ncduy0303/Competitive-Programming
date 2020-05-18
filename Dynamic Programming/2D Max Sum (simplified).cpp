// Given a 2D array of integers, find the maximum sum 2D subarray
// Idea: performing the 1D maxsum algorithm on the columns of all O(N^2) consecutive set of rows
// Time complexity: O(N^3)
// This code is used if you need to find the max sum only

#include <bits/stdc++.h>

using namespace std;

const int INF = 1 << 30;
const int MAX_N = 1000 + 5;
const int MAX_L = 20; // ~ Log N
const long long MOD = 1e9 + 7;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) (S & (-S))
#define isBitSet(S, i) ((S >> i) & 1)

int N, M, table[MAX_N][MAX_N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> N >> M;
    // Creating a prefix sum table (horizontally)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> table[i][j];
            if (j > 0) table[i][j] += table[i][j - 1];
        }
    }

    // 2D max sum subarray
    int ans = -INF;
    for (int l = 0; l < M; l++) { // looping through all pairs of columns, running kanade on a column
        for (int r = l; r < M; r++) {
            int cur = 0;
            for (int i = 0; i < N; i++) {
                if (l > 0) cur += table[i][r] - table[i][l - 1];
                else cur += table[i][r];
                cur = max(cur, 0); // restart if negative
                ans = max(ans, cur);
            }
        }
    }
    cout << "Max sum is: " << ans;
}
