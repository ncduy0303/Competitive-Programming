/* 0-1 Knapsack Problem
Given a list of items with their weights and values
Find the maximum value one can obtain with a total weight W limit
*/

#include <bits/stdc++.h>

using namespace std;

const int INF = 1 << 30;
const int MAX_N = 100000 + 5;
const int MAX_L = 20; // ~ Log N
const long long MOD = 1e9 + 7;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) (S & (-S))
#define isBitSet(S, i) ((S >> i) & 1)

int N, W, val[MAX_N], weight[MAX_N], dp[MAX_N][MAX_N], ans = 0;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    
    cin >> N >> W;
    for(int i = 0; i < N; i++) 
        cin >> val[i] >> weight[i];
    
    //Tabulation DP
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= W; j++) {
            if (i == 0 || j == 0) //base case 
                dp[i][j] = 0;
            else if (weight[i] <= j)     
                dp[i][j] = max(dp[i - 1][j], val[i] + dp[i - 1][j - val[i]]);
            else                         
                dp[i][j] = dp[i - 1][j];
        }
    }
  
    ans = dp[N][W];
    cout << ans;
}
