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

int N, arr[MAX_N], dp[MAX_N], ans = 0;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> N;
    for(int i = 0; i < N; i++)
        cin >> arr[i];

    // Solution 1 (using dynamic programming - O(n^2))
    for (int i = 0; i < N; i++) {
        dp[i] = 0;
        for (int j = i - 1; j >= 0; j--) {
            if (arr[i] > arr[j])
                dp[i] = max(dp[i], dp[j]);
        }
        dp[i]++;
        ans = max(ans, dp[i]);
    }

    //Solution 2 (using binary search - O(nlogn))
    vector<int> len(N, INF);
    for (int i = 0; i < N; i++) {
        int k = lower_bound(len.begin(), len.end(), arr[i]) - len.begin();
        len[k] = arr[i];
        ans = max(ans, k + 1);
    }
}
