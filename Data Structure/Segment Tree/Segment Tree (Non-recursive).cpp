// Segment Tree (Non-recursive, easy-to-implement version)
// Probably the one of the most advanced data structures for range queries and range updates
// Reference: https://codeforces.com/blog/entry/18051

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

int N, Q, arr[MAX_N], st[2 * MAX_N];

void build(){
    for(int i = N - 1; i > 0; i--){
        st[i] = max(st[i * 2], st[i * 2 + 1]);
    }
}

void update(int i, int val){ //assign val
    for(st[i += N] = val; i > 1; i /= 2){
        st[i / 2] = max(st[i], st[i ^ 1]);
    }
}

int rmq(int l, int r){ //range max query in [l..r)
    int ans = -INF;
    for (l += N, r += N; l < r; l /= 2, r /= 2) {
        if (l % 2 != 0) ans = max(ans, st[l++]);
        if (r % 2 != 0) ans = max(ans, st[--r]);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> N >> Q;
    for (int i = 0; i < N; i++) { //all the elements in the array are assigned as leaves in the ST
        cin >> st[i + N];
        arr[i] = st[i + N];
    }
    build();
    while (Q--) { // using 0-indexed
        int i, j; cin >> i >> j;
        cout << rmq(i, j + 1) << "\n";
    }
}
