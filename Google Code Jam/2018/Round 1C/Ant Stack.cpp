// Problem 3: Ant Stack
// Idea: DP, notice that the upper bound of the answer is only 139
// Time complexity: O(140N)

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 5;
const int MAX_L = 20; // ~ Log N
const long long MOD = 1e9 + 7;
const long long INF = 1e18;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) (S & (-S))
#define isBitSet(S, i) ((S >> i) & 1)


void solve() {
    int N; cin >> N;
    ll weight[N + 1]; for (int i = 1; i <= N; i++) cin >> weight[i];

    vector<vector<ll>> dp(N + 1, vector<ll>(140, INF));
    // dp[x][y] as the minimum sum of the weights of the ants that can form a stack of y ants where only [1..x] ants are considered, or INF if no such stack exists
    // Answer will be the largest value of y in [1..140] that dp[N][y] != INF

    // base case
    dp[0][0] = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j < 140; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j > 0 && weight[i] * 6ll >= dp[i - 1][j - 1]) {
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + weight[i]);
            }
        }
    }

    for (int i = 139; i >= 0; i--) {
        if (dp[N][i] != INF) {
            cout << i << "\n";
            return;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int tc; cin >> tc;
    for (int t = 1; t <= tc; t++) {
        cout << "Case #" << t  << ": ";
        solve();
    }
}
