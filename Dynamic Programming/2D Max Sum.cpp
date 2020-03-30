// Given a 2D array of integers, find the maximum sum 2D subarray
// Idea: performing the 1D maxsum algorithm on the columns of all O(N^2) consecutive set of rows
// Time complexity: O(N^3)

#include <bits/stdc++.h>

using namespace std;

const int INF = 1 << 30;
const int MAX_N = 1000 + 5;
const int MAX_L = 20; // ~ Log N
const long long MOD = 1e9 + 7;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) (S & (-S))
#define isBitSet(S, i) ((S >> i) & 1)

int N, M, table[MAX_N][MAX_N];

// Kadane's 1D max sum subarray on a column
int kadane(int *arr, int *start, int *finish) {
    int cur = arr[0], ans = arr[0], localStart = 0;
    for(int i = 1; i < N; i++) {
        if (cur < 0) {
            cur = 0;
            localStart = i;
        }
        cur += arr[i];
        if (cur > ans) {
            ans = cur;
            *start = localStart;
            *finish = i;
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> N >> M;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> table[i][j];

    // 2D max sum subarray
    int tmp[N], start, finish, cur, ans = -INF;
    int finalLeft, finalRight, finalTop, finalBottom;
    for (int l = 0; l < M; l++) { // looping through all pairs of columns, running kanade on a column
        memset(tmp, 0, sizeof tmp);
        for (int r = l; r < N; r++) {
            for (int i = 0; i < N; i++) {
                tmp[i] += table[i][r];
            }
            cur = kadane(tmp, &start, &finish);
            if (cur  > ans) {
                ans = cur;
                finalLeft = l;
                finalRight = r;
                finalTop = start;
                finalBottom = finish;
            }
        }
    }
    cout << "(Top, Left) (" << finalTop << ", " << finalLeft << ")\n";
    cout << "(Bottom, Right) (" << finalBottom  << ", " << finalRight << ")\n";
    cout << "Max sum is: " << ans;
}
