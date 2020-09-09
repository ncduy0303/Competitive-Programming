// N Queens Problem
// Find the total number of ways to put N queens problem on an N x N chess board
// Advanced: there will be Q queens initially placed on the chess board and B squares that cannot have queens placed on them
// Idea: complete search with pruning
// Full details here: https://dunjudge.me/analysis/problems/401/

#include <bits/stdc++.h>

using namespace std;

const int INF = 1 << 30;
const int MAX_N = 1000000 + 5;
const int MAX_L = 20; // ~ Log N
const long long MOD = 1e9 + 7;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) (S & (-S))
#define isBitSet(S, i) ((S >> i) & 1)

//all one indexed
bool row[100] = {false}, col[100] = {false}, d1[100] = {false}, d2[100] = {false};
bool check[100][100], bef[100][100];
int N, Q, B, ans = 0;

void solve(int c) {
    if (c == N + 1) { // finished, reach the last column
        ans++;
        return;
    }
    if (col[c]) solve(c + 1); // move on to the next column
    else { // test queen in each row and check
        for (int r = 1; r <= N; r++) {
            if (!check[r][c] && !row[r] && !d1[c - r + N] && !d2[c + r - 1]){
                row[r] = col[c] = d1[c - r + N] = d2[c + r - 1] = true;
                solve(c + 1);
                row[r] = col[c] = d1[c - r + N] = d2[c + r - 1] = false;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> N >> Q;
    for (int i = 0; i < Q; i++) {
        int r, c; cin >> r >> c;
        if (!row[r] && !d1[c - r + N] && !d2[c + r - 1])
            row[r] = col[c] = d1[c - r + N] = d2[c + r - 1] = true;
        else {
            cout << 0;
            return 0;
        }
        bef[r][c] = true;
    }
    cin >> B;
    for (int i = 0; i < B; i++) {
        int r, c; cin >> r >> c;
        if (!bef[r][c])
            check[r][c] = true;
        else {
            cout << 0;
            return 0;
        }
    }
    solve(1);
    cout << ans;
}
