// Answer range query for static array
// O(nlogn) construction
// Usually O(logn) for each query, but can be modified to be O(1) for queries that can overlap (i.e minimum/maximum, gcd)

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

int N, Q, arr[MAX_N], table[MAX_N][MAX_L + 1], lg[MAX_N + 1];

void build_log_table() { // for O(1) range minimum query
    lg[1] = 0;
    for (int i = 2; i <= N; i++)
        lg[i] = lg[i/2] + 1;
}

void build_sparse_table() { // O(nlogn)
    for(int i = 1; i <= N; i++)
        table[i][0] = arr[i];

    for(int j = 1; j <= MAX_L; j++) {
        for(int i = 1; i + (1 << j) <= N + 1; i++)
            table[i][j] = min(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
    }
}

int rmq(int l, int r){ // range minimum query in O(1)
    int j = lg[r - l + 1];
    return min(table[l][j], table[r - (1 << j) + 1][j]);
}

int rsq(int l, int r) { //range sum query in O(logn)
    int sum = 0;
    for (int j = MAX_L; j >= 0; j--) {
        if ((1 << j) <= r - l + 1) {
            sum += table[l][j];
            l += 1 << j;
        }
    }
    return sum;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> N >> Q;
    for(int i = 1; i <= N; i++) {
        cin >> arr[i];
    }
    build_sparse_table();
    build_log_table();
    while(Q--) {
        int t; cin >> t;
        if (t == 0) { // rsq
            int x, y; cin >> x >> y;
            cout << rsq(x, y) << "\n";
        }
        else { // rmq
            int x, y; cin >> x >> y;
            cout << rmq(x, y) << "\n";
        }
    }
}
