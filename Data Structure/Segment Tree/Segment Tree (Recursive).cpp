// Segment Tree (Recursive, basic implementation)
// Probably the one of the most advanced data structures for range queries and range updates
// Here use 1-index

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

int N, Q, arr[MAX_N], st[4 * MAX_N];

void build(int node, int start, int end) {
    if(start == end)
        st[node] = arr[start];
    else {
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        st[node] = st[2 * node] + st[2 * node + 1];
    }
}

void update(int node, int start, int end, int idx, int val){ //add val to arr[idx]
    if (start == end) {
        arr[idx] += val;
        st[node] += val;
    }
    else {
        int mid = (start + end) / 2;
        update(2 * node, start, mid, idx, val);
        update(2 * node + 1, mid + 1, end, idx, val);
        st[node] = st[2 * node] + st[2 * node + 1];
    }
}

int rsq(int node, int start, int end, int l, int r){ //range sum query in [l..r]
    if(start > r || end < l) return 0; // remember to change to INF for min query
    if(start >= l && end <= r) return st[node];

    int mid = (start + end) / 2;
    return rsq(2 * node, start, mid, l, r) + rsq(2 * node + 1, mid + 1, end, l, r);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> N >> Q;
    for (int i = 1; i <= N; i++) { // using 1-indexed
        cin >> arr[i];
    }
    build(1, 1, N);
    while (Q--) {
        int t; cin >> t;
        if (t == 0) { // update
            int idx, val; cin >> idx >> val;
            update(1, 1, N, idx, val);
        }
        else {
            int l, r; cin >> l >> r;
            cout << rsq(1, 1, N, l, r) << "\n";
        }
    }
}
