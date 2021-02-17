#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

// standard treap with split and merge
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
struct tdata {
    int val, pri, sz;
    tdata *ln = NULL, *rn = NULL;
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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
}