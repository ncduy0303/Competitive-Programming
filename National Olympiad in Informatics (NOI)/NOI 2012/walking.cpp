/* NOI 2012 - Walking
Solution: define two sorted arrays to keep track of the order of the departure time and the arrival time (in reverse),
          The problem can be converted into finding the longest common subsequence (LCS) between the two arrays
Time complexity: O(n^2)
*/

#include <bits/stdc++.h>

using namespace std;

const int INF = 1 << 30;
const int MAX_N = 500 + 5;
const int MAX_L = 20; // ~ Log N
const long long MOD = 1e9 + 7;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) (S & (-S))
#define isBitSet(S, i) ((S >> i) & 1)

int N, L, dp[MAX_N][MAX_N];
vector<pair<double, int> > tin, tout;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin >> L >> N;
    for(int i = 0; i < N; i++) {
        double t, v; cin >> t >> v;
        tin.push_back({t, i});
        tout.push_back({L / v + t, i});
    }
    sort(tin.begin(), tin.end());
    sort(tout.rbegin(), tout.rend());
    for(int i = 1; i <= N; i++)
        for(int j = 1; j <= N; j++)
            dp[i][j] = (tin[i - 1].second == tout[j - 1].second) ? dp[i - 1][j - 1] + 1 : max(dp[i - 1][j], dp[i][j - 1]);
    cout << dp[N][N];
}
