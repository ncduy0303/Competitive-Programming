// Basically, use DP to generate C(n, k)

// If you need to calculate a lot of C(n, k) for all values n <= some constant,
// simulate Pascal Triangle and save all values into a 2D array => Time complexity: O(n^2)
// This usually serves as an intermediate step for a more difficult DP problem

// If you only need to calculate C(n, k) for a few times,
// just apply the formula directly C(n, k) = n!/(k!(n-k)!) with time complexity O(k) per query

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

void pascal(int n) {
    int C[n + 1][n + 1];
    for (int i = 1; i <= n; i++) C[0][i] = 0; // C(0, i) = 0
    for (int i = 0; i <= n; i++) C[i][0] = 1; // C(i, 0) = 1

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            C[i][i] = C[i - 1][j - 1] + C[i - 1][j]; // Pascal Triangle: C(i, j) = C(i - 1, j - 1) + C(i - 1, j)
}

int coefficient(int n, int k) {
    int res = 1;
    k = min(k, n - k); // as C(n, k) = C(n, n - k)
    for (int i = 0; i < k; i++) {
        res *= (n - i);
        res /= (i + 1);
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    
    int n, k; cin >> n >> k;
    cout << coefficient(n, k);
}
