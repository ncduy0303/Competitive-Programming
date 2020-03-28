/* NOI 2018: Journey
Idea: Dynamic Programming (let state dp[C][D] be the number of ways to reach city C in D days)
      Transition: reach city C in less than D days and wait or only reach city C on the D-th days
Time Complexity: O(N*M*H)
*/

#include <bits/stdc++.h>

using namespace std;

const int INF = 1 << 30;
const int MAX_N = 50000 + 5;
const int MAX_L = 20; // ~ Log N
const long long MOD = 1e9 + 7;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) (S & (-S))
#define isBitSet(S, i) ((S >> i) & 1)

int N, M, H, dp[10000][400];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> N >> M >> H;
    dp[0][0] = 1; //base case

    for(int i = 0; i < N - 1; i++) {
        for(int j = 0; j < H; j++) {
            int c, d; cin >> c >> d;
            if (i < c) { // correct direction
                int s = 0;
                for(int k = 0; k < M - d; k++) {
                    s = min(s + dp[i][k], 500000001);
                    dp[c][d + k] = min(dp[c][d + k] + s , 500000001);
                }
            }
        }
    }

    for(int i = 0; i < M; i++)
        cout << dp[N - 1][i] << " ";
}
