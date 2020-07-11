// Problem link: https://www.spoj.com/problems/GSS3/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 5e4 + 5;
const int INF = 1e9 + 7;

struct tdata {
    int sum, ans, pref, suff;
    tdata() { // need to have this line to initialize the array
        sum = ans = pref = suff = 0;
    }
    tdata(int val) {
        sum = ans = pref = suff = val;
    }
    tdata(tdata l, tdata r) {
        sum = l.sum + r.sum;
        pref = max(l.pref, l.sum + r.pref);
        suff = max(r.suff, r.sum + l.suff);
        ans = max({l.ans, r.ans, l.suff + r.pref});
    }
};

int N, Q;
int arr[MAX_N];
tdata st[4 * MAX_N];

void build(int node, int start, int end) {
    if (start == end) st[node] = tdata(arr[start]);
    else {
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        st[node] = tdata(st[2 * node], st[2 * node + 1]);
    }
}

/*void down(int node, int start, int end) {
    if (st[node].addval) {
        int mid = (start + end) / 2;
        ll val = st[node].addval;
        st[2 * node].addval += val;
        st[2 * node + 1].addval += val;
        st[2 * node].sum += val * (mid - start + 1);
        st[2 * node + 1].sum += val * (end - mid);
        st[node].addval = 0;
    }
}

void update(int node, int start, int end, int l, int r, ll val) {
    if (r < start || end < l) return;
    if (l <= start && end <= r) {
        st[node].sum += val * (end - start + 1);
        st[node].addval += val;
    }
    else {
        down(node, start, end);
        int mid = (start + end) / 2;
        update(2 * node, start, mid, l, r, val);
        update(2 * node + 1, mid + 1, end, l, r, val);
        st[node].sum = st[2 * node].sum + st[2 * node + 1].sum;
    }
}

ll query(int node, int start, int end, int l, int r) {
    if (r < start || end < l) return 0;
    if (l <= start && end <= r) return st[node].sum;
    else {
        down(node, start, end);
        int mid = (start + end) / 2;
        return query(2 * node, start, mid, l, r) + query(2 * node + 1, mid + 1, end, l, r);
    }
}*/

void update(int node, int start, int end, int idx, int val) {
    if (start == end) {
        arr[idx] = val;
        st[node] = tdata(val);
    }
    else {
        int mid = (start + end) / 2;
        if (idx <= mid) update(2 * node, start, mid, idx, val);
        else update(2 * node + 1, mid + 1, end, idx, val);
        st[node] = tdata(st[2 * node], st[2 * node + 1]);
    }
}

tdata query(int node, int start, int end, int l, int r) {
    if (l > r) return tdata(-INF);
    if (start == l && end == r) return st[node];
    int mid = (start + end) / 2;
    return tdata(query(2 * node, start, mid, l , min(r, mid)),
                 query(2 * node + 1, mid + 1, end, max(l, mid + 1), r));
}

void solve() {
    memset(st, 0, sizeof st);
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> arr[i];
    build(1, 1, N);
    cin >> Q;
    while (Q--) {
        char c; cin >> c;
        if (c == '0') {
            int idx, val; cin >> idx >> val;
            update(1, 1, N, idx, val);
        }
        else {
            int l, r; cin >> l >> r;
            cout << query(1, 1, N, l, r).ans << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int tc; tc = 1;
    for (int i = 1; i <= tc; i++) {
        solve();
    }
}
