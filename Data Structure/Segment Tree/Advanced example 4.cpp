// Segment Tree
// Problem link: https://www.spoj.com/problems/BGSHOOT/
// Possible coordinates range are 1e9 which are to big to fit in the segment tree, so we need to compress them
// There are only 1e5 pair of points, so we just need to compress the points using map

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 2e5 + 5;

struct tdata {
    int val;
};

int N, Q;
map<int, int> compress;
pair<int, int> seg[MAX_N], qq[MAX_N];
int arr[MAX_N];
tdata st[4 * MAX_N];

void build(int node, int start, int end) {
    if (start == end) {
        st[node].val = arr[start];
    }
    else {
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        st[node].val = max(st[2 * node].val, st[2 * node + 1].val);
    }
}

int query(int node, int start, int end, int l, int r) {
    if (l > r) return 0;
    if (start == l && end == r) return st[node].val;
    int mid = (start + end) / 2;
    return max(query(2 * node, start, mid, l , min(r, mid)),
               query(2 * node + 1, mid + 1, end, max(l, mid + 1), r));
}

void solve() {
    memset(st, 0, sizeof st);
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> seg[i].first >> seg[i].second;
        compress[seg[i].first] = compress[seg[i].second] = 1;
    }
    cin >> Q;
    for (int i = 1; i <= Q; i++) {
        cin >> qq[i].first >> qq[i].second;
        compress[qq[i].first] = compress[qq[i].second] = 1;
    }
    int cnt = 0;
	for (auto &x: compress)
		x.second = ++cnt;
    for (int i = 1; i <= N; i++) {
        arr[compress[seg[i].first]]++;
        arr[compress[seg[i].second] + 1]--;
    }
    for (int i = 1; i <= MAX_N - 1; i++)
        arr[i] += arr[i - 1];

    build(1, 1, MAX_N - 1);
    for (int i = 1; i <= Q; i++) {
        cout << query(1, 1, MAX_N - 1, compress[qq[i].first], compress[qq[i].second]) << "\n";
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
