// Treap data structure supporting split and merge function
// Problem link: https://codeforces.com/gym/102787/problem/A

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
struct tdata {
    int val, pri, sz;
    tdata *ln, *rn;
    tdata(int val): val(val), pri(rng()), sz(1), ln(), rn() {} 
};
int sz(tdata *node) {return node ? node->sz : 0;}
void propagate(tdata *node) {
    if (!node) return;
}
void combine(tdata *node) {
    if (!node) return;
    propagate(node->ln); propagate(node->rn);
    node->sz = sz(node->ln) + sz(node->rn) + 1;
}
void heapify(tdata *node) {
    if (!node) return;
    auto mx = node;
    if (node->ln && node->ln->pri > node->pri) mx = node;
    if (node->rn && node->rn->pri > node->pri) mx = node;
    if (node != mx) {
        swap(node->pri, mx->pri);
        heapify(mx);
    }
}
tdata* build(vector<int> &arr, int start, int end) {
    if (start > end) return NULL;
    int mid = (start + end) / 2;
    auto node = new tdata(arr[mid]);
    node->ln = build(arr, start, mid - 1);
    node->rn = build(arr, mid + 1, end);
    heapify(node); combine(node);
    return node;
}
void split(tdata *node, tdata *&ln, tdata *&rn, int k) { // k nodes to ln
    propagate(node);
    if (!node) {
        ln = rn = NULL;
        return;
    }
    if (sz(node->ln) >= k) split(node->ln, ln, node->ln, k), rn = node;
    else split(node->rn, node->rn, rn, k - sz(node->ln) - 1), ln = node;
    combine(node);
}
void merge(tdata *&node, tdata *ln, tdata *rn) {
    propagate(ln); propagate(rn);
    if (!ln || !rn) {
        node = ln ? ln : rn;
        return;
    }
    if (ln->pri > rn->pri) merge(ln->rn, ln->rn, rn), node = ln;
    else merge(rn->ln, ln, rn->ln), node = rn;
    combine(node);
}
void print(tdata *node) {
    if (!node) return;
    print(node->ln);
    cout << node->val << " ";
    print(node->rn);
}

void solve() {
    int n; cin >> n;
    vector<int> arr(n);
    iota(arr.begin(), arr.end(), 1);
    auto tr = build(arr, 0, n - 1);
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b; 
        if (a >= b) continue;
        int len = min(b - a, n - b + 1);
        tdata *p1, *p2, *p3, *p4, *p5;
        split(tr, p3, p4, b - 1);
        split(p4, p4, p5, len);
        split(p3, p1, p2, a - 1);
        split(p2, p2, p3, len);
        merge(tr, p1, p4);
        merge(tr, tr, p3);
        merge(tr, tr, p2);
        merge(tr, tr, p5);
    }
    print(tr);
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int tc = 1;
    // cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t  << ": ";
        solve();
    }
}