// An example of lazy propagation on segment tree
// range update: add val to all elements in the range [l, r]
// range query: return the minimum element in the range [l, r]
// Idea: similar to normal segment tree, but there are 2 main additional details
// 1) Each node now store a lazy value
// 2) Implement a down function: to push the lazy value of a node to its children

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 2e5 + 5;

struct tdata {
    int lazy;
    int val;
};

int N, Q, arr[MAX_N];
tdata st[4 * MAX_N];

void build(int node, int start, int end) {
    if (start == end) {
        st[node].val = arr[start];
        st[node].lazy = 0;
    }
    else {
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        st[node].val = min(st[2 * node].val, st[2 * node + 1].val);
    }
}

void down(int node) { // push the lazy value from a node to its children
    int lazy = st[node].lazy;
    st[2 * node].lazy += lazy;
    st[2 * node].val += lazy;
    st[2 * node + 1].lazy += lazy;
    st[2 * node + 1].val += lazy;
    st[node].lazy = 0;
}

void update(int node, int start, int end, int l, int r, int val) { // increase all members in [l, r] by val
    if (r < start || end < l) return;
    if (l <= start && end <= r) {
        st[node].val += val;
        st[node].lazy += val;
    }
    else {
        int mid = (start + end) / 2;
        down(node);
        update(2 * node, start, mid, l, r, val);
        update(2 * node + 1, mid + 1, end, l, r, val);
        st[node].val = min(st[2 * node].val, st[2 * node + 1].val);
    }
}

int query(int node, int start, int end, int l, int r) {
    if (r < start || end < l) return INT_MAX;
    if (l <= start && end <= r) return st[node].val;
    else {
        int mid = (start + end) / 2;
        down(node);
        return min(query(2 * node, start, mid, l, r), query(2 * node + 1, mid + 1, end, l, r));
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> N >> Q;
    for (int i = 1; i <= N; i++) cin >> arr[i];
    build(1, 1, N);
    while (Q--) {
        char c; cin >> c;
        if (c == 'U') {
            int l, r, val; cin >> l >> r >> val;
            update(1, 1, N, l, r, val);
        }
        else {
            int l, r; cin >> l >> r;
            cout << query(1, 1, N, l, r) << "\n";
        }
    }
}

/*
Example input:
8 6
1 2 3 4 5 6 7 8
Q 2 5
Q 6 6
U 3 7 2
Q 2 5
U 6 6 -1
Q 6 6

Expected output:
2
6
2
7
*/
