// Persistent Segment Tree
// Same as normal segment tree, but we can make queries on different versions of the tree after many updates
// This is done by efficiently creating new nodes to store older versions without storing the whole tree after every updates

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 2e5 + 5;

struct tdata {
    int left, right;    // ID of left child & right child
    int val;            // Max value of node
    tdata() {}
    tdata(int val, int left, int right) : val(val), left(left), right(right) {}
};  // Each node has a position in this array, called ID

int N, Q, arr[MAX_N], ver[MAX_N];
int nNode = 0, nVer = 0;
tdata st[6 * MAX_N];

// Update max value of a node (very important function)
void refine(int node) {
    st[node].val = max(st[st[node].left].val, st[st[node].right].val);
}

void build(int node, int start, int end) {
    if (start == end)
        st[++nNode] = tdata(arr[start], 2 * nNode, 2 * nNode + 1);
    else {
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        refine(node);
    }
}

int update(int node, int start, int end, int idx, int val) { // set arr[idx] to val
    nNode++; // this line is very important
    if (start == end) {
        arr[idx] = val;
        st[nNode] = tdata(val, 0, 0);
    }
    else {
        int mid = (start + end) / 2;
        if (idx <= mid) {
            st[nNode].left = update(st[node].left, start, mid, idx, val);
            st[nNode].right = st[node].right;
        }
        else {
            st[nNode].left = st[node].left;
            st[nNode].right = update(st[node].right, mid + 1, end, idx, val);
        }
        refine(node);
    }
    return nNode;
}

int query(int node, int start, int end, int l, int r) {
    if (l > r) return -INT_MAX;
    if (start == l && end == r) return st[node].val;

    int mid = (start + end) / 2;
    return max(query(st[node].left, start, mid, l, min(r, mid)), query(st[node].right, mid + 1, end, max(l, mid + 1), r));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> N >> Q;
    for (int i = 1; i <= N; i++) cin >> arr[i];
    build(1, 1, N);

    // update
    //ver[++nVer] = update(ver[nVer - 1], 1, N, idx, val);

    // query (at time t)
    //int res = query(ver[t], 1, N, l, r);
}

