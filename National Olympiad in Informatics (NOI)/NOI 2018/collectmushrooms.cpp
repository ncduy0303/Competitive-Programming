/* NOI 2018 - : CollectingMushrooms
Idea: 2D Prefix Sum to count the number of reachable sprinklers for each box
Time Complexity: O(RC)
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

int R, C, D, K;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> R >> C >> D >> K;
    char grid[R + 1][C + 1];
    for(int i = 1; i <= R; i++)
        for(int j = 1; j <= C; j++)
            cin >> grid[i][j];

    int sum[R + 1][C + 1];
    for(int i = 0; i <= R; i++) {
        for(int j = 0; j <= C; j++) {
            if(i == 0 || j == 0)
                sum[i][j] = 0;
            else {
                int cur = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
                if(grid[i][j] == 'S') cur++;
                sum[i][j] = cur;
            }
        }
    }

    int cnt = 0;
    for(int i = 1; i <= R; i++) {
        for(int j = 1; j <= C; j++){
            if(grid[i][j] == 'M') {
                int t, r, b, l; //top, right, bottom, left
                t = max(1, i - D);
                b = min(R, i + D);
                l = max(1, j - D);
                r = min(C, j + D);
                if(sum[b][r] - sum[b][l - 1] - sum[t - 1][r] + sum[t - 1][l - 1] >= K) cnt++;
            }
        }
    }
    cout << cnt;
}

