// Persistent segment tree for range sum query, point set update 
// Here implement with pointers
// Problem link: https://cses.fi/problemset/task/1737

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 2e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

struct tdata {
    tdata *l, *r;
    ll sum;
    tdata() {}
    tdata(tdata* l, tdata* r, int val) : l(l), r(r), sum(val) {}
};

int n, q, cnt, arr[MAX_N];
tdata *ver[MAX_N];

void build(tdata *node, int start, int end) {
    if (start == end) {
        node->sum = arr[start];
        return;
    }
    node->l = new tdata(); node->r = new tdata();
    int mid = (start + end) / 2;
    build(node->l, start, mid);
    build(node->r, mid + 1, end);
    node->sum = node->l->sum + node->r->sum;
}

void update(tdata *node, int start, int end, int idx, int val) {
    if (start == end) {
        node->sum = val;
        return;
    }
    int mid = (start + end) / 2;
    if (idx <= mid) {
        tdata *l = node->l;
        node->l = new tdata(l->l, l->r, l->sum);
        update(node->l, start, mid, idx, val);
    }
    else {
        tdata *r = node->r;
        node->r = new tdata(r->l, r->r, r->sum);
        update(node->r, mid + 1, end, idx, val);
    }
    node->sum = node->l->sum + node->r->sum;
}

ll query(tdata *node, int start, int end, int l, int r) {
    if (r < start || end < l) return 0;
    if (l <= start && end <= r) return node->sum;
    int mid = (start + end) / 2;
    return query(node->l, start, mid, l, r) + query(node->r, mid + 1, end, l, r);
}

void solve() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> arr[i];
    ver[++cnt] = new tdata();
    build(ver[cnt], 1, n);
    while (q--) {
        int t, k; cin >> t >> k;
        if (t == 1) {
            int a, x; cin >> a >> x;
            update(ver[k], 1, n, a, x);
        }
        else if (t == 2) {
            int a, b; cin >> a >> b;
            cout << query(ver[k], 1, n, a, b) << "\n";
        }
        else {
            ver[++cnt] = new tdata(ver[k]->l, ver[k]->r, ver[k]->sum);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int tc; tc = 1;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t  << ": ";
        solve();
    }
}