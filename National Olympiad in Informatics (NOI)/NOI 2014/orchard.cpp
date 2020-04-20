/* NOI 2014 - Orchard
Idea: Dynamic Programming
Time Complexity: O(N^2*M)
*/

#include <bits/stdc++.h>

using namespace std;

const int INF = 1 << 30;
const int MAX_N = 500000 + 5;
const int MAX_L = 20; // ~ Log N
const long long MOD = 1e9 + 7;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) (S & (-S))
#define isBitSet(S, i) ((S >> i) & 1)

int V, E, Q, par[MAX_N], dist[MAX_N] = {0};
vector<pair<int, int> > adj[MAX_N];
vector<pair<int, pair<int, int> > > EdgeList;

int N, M, num_of_1 = 0;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> N >> M;
    int arr[N][M], dp[N+ 1][M];
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> arr[i][j];
            if (arr[i][j] == 1) num_of_1++;
        }
    }
    for (int j = 0; j < M; j++) {
        int sum = 0;
        for (int i = 0; i < N; i++) {
            sum += arr[i][j];
            dp[i + 1][j] = sum;
        }
    }
    int min_cost = num_of_1 - 1;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j <= N; j++) {
            int cur = num_of_1;
            for (int k = 0; k < M; k++) {
                int t = j - i + 2 * (dp[i][k] - dp[j][k]);
                cur = min(cur + t, num_of_1 + t);
                min_cost = min(min_cost, cur);
            }
        }
    }
    cout << min_cost;
}
