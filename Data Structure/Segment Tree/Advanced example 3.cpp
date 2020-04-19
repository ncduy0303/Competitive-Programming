// Problem: https://cses.fi/problemset/task/1143/
// Idea: descending the tree: by moving each time to the left or the right,
// depending on the maximum value of the left child

#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;
const int MAX_N = 200000 + 5;
const int MAX_L = 20; // ~ Log N
const long long MOD = 1e9 + 7;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) (S & (-S))
#define isBitSet(S, i) ((S >> i) & 1)

int N, Q, st[4 * MAX_N];

void update(int node, int start, int end, int idx, int val){ //add val to arr[idx]
    if (start == end) {
        st[node] += val;
    }
    else {
        int mid = (start + end) / 2;
        if (idx <= mid) update(2 * node, start, mid, idx, val);
        else update(2 * node + 1, mid + 1, end, idx, val);
        st[node] = max(st[2 * node], st[2 * node + 1]);
    }
}

int rmq(int node, int start, int end, int l, int r){ //range sum query in [l..r]
    if (l > r) return -INF;
    if (start == l && end == r) return st[node];

    int mid = (start + end) / 2;
    return max(rmq(2 * node, start, mid, l, min(r, mid)), rmq(2 * node + 1, mid + 1, end, max(l, mid + 1), r));
}

int getFirstGreater(int node, int start, int end, int l, int r, int val) { // descending the tree
    if (start == end) {
        return st[node] >= val ? l : -1;
    }
    int mid = (start + end) / 2;
    int cur = rmq(2 * node, start, mid, l, min(r, mid));
    if (cur >= val)
        return getFirstGreater(2 * node, start, mid, l, min(r, mid), val);
    else
        return getFirstGreater(2 * node + 1, mid + 1, end, max(l, mid + 1), r, val);
}

void solve() {
    cin >> N >> Q;
    for (int i = 0; i < N; i++) { // using 1-indexed
        int val; cin >> val;
        update(1, 0, N - 1, i, val);
    }
    while (Q--) {
        int val; cin >> val;
        int idx = getFirstGreater(1, 0, N - 1, 0, N - 1, val);
        if (idx == -1) cout << 0 << " ";
        else {
            cout << idx + 1<< " ";
            update(1, 0, N - 1, idx, -val);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    solve();
}
