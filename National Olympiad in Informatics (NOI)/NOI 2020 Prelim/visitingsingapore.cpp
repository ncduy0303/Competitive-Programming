/* NOI 2020 Prelim: Visiting Singapore
Idea: Dynamic Programming
Time Complexity: O(NM)
*/

#include <bits/stdc++.h>

using namespace std;

const int INF = 1 << 30;
const int MAX_N = 300000 + 5;
const int MAX_L = 20; // ~ Log N
const long long MOD = 1e9 + 7;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) (S & (-S))
#define isBitSet(S, i) ((S >> i) & 1)

int K, N, M, A, B, V[1005], S[5005], T[5005], ans = 0;
int dp[3][5005]; //max happiness - idx * b
int dp1[3][5005], dp2[3][5005], dp3[3][5005]; // memory optimization from 4 x N x M to 4 x 4 x M

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> K >> N >> M >> A >> B;
    A = - A; B = - B;
    for(int i = 1; i <= K; i++) cin >> V[i];
    for(int i = 2; i < N + 2; i++) cin >> S[i];
    for(int i = 2; i < M + 2; i++) cin >> T[i];

    //base cases
    for(int i = 0; i < 2; i++) {
		for(int j = 0; j < M + 2; j++) {
			dp[i][j] = 2 * B;
			dp1[i][j] = dp2[i][j] = dp3[i][j] = -INF;
		}
	}

	ans = -(A + M * B);
	for(int i = 2; i < N + 2; i++) {
        int x = i % 3, y = (i + 1) % 3;
        for(int j = 2; j < M + 2; j++) {
            dp[x][j] = 2 * B;
            dp1[x][j] = dp2[x][j] = dp3[x][j] = -INF;
            if(S[i] == T[j]) { // can visit event (i, j)
                dp3[x][j] = V[T[j]] - (j - 2) * B + (j + 1) * B + (i + 1) * B - A;
                if(j == 2) dp3[x][j] += A; // if this is the first event
                dp3[x][j] = max(dp3[x][j], max(dp3[(i + 2) % 3][j - 1], dp[y][j - 2] - 2 * A) + V[T[j]] + 2 * B);
				dp3[x][j] = max(dp3[x][j], max(dp1[(i + 2) % 3][j - 1], dp2[(i + 2) % 3][j - 1]) + V[T[j]] - A + 2 * B);
            }
            dp1[x][j] = max(dp1[x][j - 1], dp3[x][j]);
            dp2[x][j] = max(dp2[(i + 2) % 3][j], dp3[x][j]);
            dp[x][j] = max(dp[x][j], max(dp3[x][j], max(dp[(i + 2) % 3][j], dp[x][j - 1])));
            int cur = dp3[x][j] - (M + 2) * B - (i + 1) * B - A;
			if (j == M + 1) cur += A;
			ans = max(ans, cur);
        }
	}
	cout << ans;
}
