// Cutting sticks problem
// Given a length L and N cutting points, find the minimum cost perform all N cuts
// The cost of a cut is equal to the length of the stick that we are cutting
// Example: UVa/10003 https://onlinejudge.org/external/100/10003.pdf

#include <bits/stdc++.h>

using namespace std;

const int INF = 1 << 30;
const int MAX_N = 100 + 5;
const int MAX_L = 20; // ~ Log N
const long long MOD = 1e9 + 7;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) (S & (-S))
#define isBitSet(S, i) ((S >> i) & 1)

int L, N, arr[MAX_N], dp[MAX_N][MAX_N], sv[MAX_N][MAX_N];
// dp[i][j] stores the minimum cost of cutting between points i and j

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin >> L >> N;
    for (int i = 1; i <= N; i++) cin >> arr[i];
    arr[0] = 0; arr[N + 1] = L; // adding the beginning point and the ending point

    // Time complexity: O(N^3)
    for (int len = 0; len <= N; len++) { // try all length of the stick
        for (int i = 0, j = len + 1; j <= N + 1; i++, j++) { // try all possible left points
            if (len == 0) dp[i][j] = 0;
            else {
                dp[i][j] = INF;
                for (int k = i + 1; k < j; k++) { // try all possible intermediate points
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
                }
                dp[i][j] += arr[j] - arr[i]; // cost(i, j)
            }
        }
    }
    cout << dp[0][N + 1]; 

    // Knuth Optimization to O(N^2)
    // Condition: dp[i][j] = min{i < k < j}(dp[i][k] + dp[k][j]) + C[i][j]
    // Reference: http://www.cse.unsw.edu.au/~cs4128/18s1/lectures/7-dp2.pdf
    for (int i = 0; i <= N; i++)
        sv[i][i + 1] = i;

    for (int len = 0; len <= N; len++) { // try all length of the stick
        for (int i = 0, j = len + 1; j <= N + 1; i++, j++) { // try all possible left points
            if (len == 0) dp[i][j] = 0;
            else {
                dp[i][j] = INF;
                for (int k = sv[i][j - 1]; k <= sv[i + 1][j]; k++) { // optimize by restricting the range of k
                    if (dp[i][k] + dp[k][j] < dp[i][j]) {
                        sv[i][j] = k;
                        dp[i][j] = dp[i][k] + dp[k][j];
                    }
                }
                dp[i][j] += arr[j] - arr[i]; // cost(i, j)
            }
        }
    }
    cout << dp[0][N + 1];
}
