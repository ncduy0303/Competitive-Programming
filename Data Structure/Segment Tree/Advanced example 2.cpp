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

int N, Q, arr[MAX_N];
set<int> st[4 * MAX_N];

set<int> combine(set<int> l, set<int> r) {
    set<int> res;
    merge(l.begin(), l.end(), r.begin(), r.end(), inserter(res, res.begin()));
    return res;
}

set<int> make(int val) {
    set<int> res;
    if (val != -1) res.insert(val);
    return res;
}

void build(int node, int start, int end) {
    if(start == end)
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

set<int> query(int node, int start, int end, int l, int r){ // query in [l..r]
    if (l > r) return make(-1);
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
        int l, r; cin >> l >> r;
        l--; r--;
        cout << query(1, 0, N - 1, l, r).size() << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    solve();
}
