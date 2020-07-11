// Problem: https://cses.fi/problemset/task/1190
// We can store more than one piece of information in each node of the segment tree
// User-defined merge function

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

struct tdata {
    ll sum, pref, suff, ans;
};

int N, Q, arr[MAX_N];
tdata st[4 * MAX_N];

tdata make(int val) {
    tdata res;
    res.sum = val;
    res.ans = res.pref = res.suff = max(0, val);
    return res;
}

tdata combine(tdata l, tdata r) {
    tdata res;
    res.sum = l.sum + r.sum;
    res.pref = max(l.pref, l.sum + r.pref);
    res.suff = max(r.suff, r.sum + l.suff);
    res.ans = max(max(l.ans, r.ans), l.suff + r.pref);
    return res;
}

void build(int node, int start, int end) {
    if (start == end)
        st[node] = make(arr[start]);
    else {
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        st[node] = combine(st[2 * node], st[2 * node + 1]);
    }
}

void update(int node, int start, int end, int idx, int val) { // change arr[idx] to val
    if (start == end) {
        arr[idx] = val;
        st[node] = make(val);
    }
    else {
        int mid = (start + end) / 2;
        if (idx <= mid) update(2 * node, start, mid, idx, val);
        else update(2 * node + 1, mid + 1, end, idx, val);
        st[node] = combine(st[2 * node], st[2 * node + 1]);
    }
}

tdata query(int node, int start, int end, int l, int r){ // query in [l..r]
    if (l > r) return make(0);
    if (start == l && end == r) return st[node];

    int mid = (start + end) / 2;
    return combine(query(2 * node, start, mid, l, min(r, mid)),
                   query(2 * node + 1, mid + 1, end, max(l, mid + 1), r));
}

void solve() {
    cin >> N >> Q;
    for (int i = 0; i < N; i++) cin >> arr[i];
    build(1, 0, N - 1);
    while (Q--) {
        int idx, val; cin >> idx >> val;
        idx--;
        update(1, 0, N - 1, idx, val);
        cout << query(1, 0, N - 1, 0, N - 1).ans << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    solve();
}
