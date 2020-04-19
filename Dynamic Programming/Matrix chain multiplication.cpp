// Matrix Chain Mulitiplication
// Given N matrixs with dimensions p0 x p1, p1 x p2, ... , pn-1 x pn
// Find the minimum number of scalar multiplications to carry out the matrix multiplication
// Time complexity: O(N^3)

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

int N, p[MAX_N], dp[MAX_N][MAX_N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> N;
    // Matrix Ai has dimension p[i-1] x p[i] for i = 1..N
    for (int i = 0; i <= N; i++) cin >> p[i];

    // cost is zero when multiplying one matrix
    for (int i = 1; i <= N; i++) dp[i][i] = 0;
    // length is one
    for (int i = 1; i <= N - 1; i++) dp[i][i + 1] = p[i - 1] * p[i] * p[i + 1];
    // l is the length of the chain
    for (int l = 2; l <= N - 1; l++) {
        for (int i = 1, j = i + l; j <= N; i++, j++) {
            dp[i][j] = INF;
            for (int k = i; k <= j - 1; k++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + p[i - 1] * p[k] * p[j]);
            }
        }
    }
    cout << dp[1][N];
}
