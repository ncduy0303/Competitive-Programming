// Coin change problem
// Given N different values of coins
// 1) Find different combinations of these coins (there is an infinite supply of each coin value) to sum up to V
// 2) Find the minimum coins required to sum up to V

#include <bits/stdc++.h>

using namespace std;

const int INF = 1 << 30;
const int MAX_N = 100 + 5;
const int MAX_V = 100000 + 5;
const int MAX_L = 20; // ~ Log N
const long long MOD = 1e9 + 7;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) (S & (-S))
#define isBitSet(S, i) ((S >> i) & 1)

int N, V, coin[MAX_N], dp[MAX_V];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> N >> V;
    for(int i = 0; i < N; i++) cin >> coin[i];

    // 1) Coin change ways
    memset(dp, 0, sizeof dp); 
    dp[0] = 1; // there is one way to sum up to 0
    for (int i = 0; i < N; i++)
        for (int v = coin[i]; v <= V; v++)
            dp[v] += dp[v - coin[i]];
    cout << dp[V];
    
    // 2) Coin change min
    memset(dp, -1, sizeof dp); //-1 represents no way here
    dp[0] = 0;
    for (int i = 0; i < N; i++) {
        for (int v = coin[i]; v <= V; v++) {
            if (dp[v - coin[i]] == -1) continue;
            if (dp[v] == -1) dp[v] = dp[v - coin[i]] + 1;
            dp[v] = min(dp[v], dp[v - coin[i]] + 1);
        }
    }
    cout << dp[V];
}
