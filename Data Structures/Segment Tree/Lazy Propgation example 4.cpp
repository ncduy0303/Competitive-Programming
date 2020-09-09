// Problem link: https://www.spoj.com/problems/MULTQ3/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 1e5 + 5;

struct tdata {
    int mod0, mod1, mod2, lazy;
};

int N, Q, arr[MAX_N];
tdata st[4 * MAX_N];

void build(int node, int start, int end) {
    if (start == end) {
        st[node].mod0 = (arr[start] % 3 == 0);
        st[node].mod1 = (arr[start] % 3 == 1);
        st[node].mod2 = (arr[start] % 3 == 2);
        st[node].lazy = 0;
    }
    else {
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        st[node].mod0 = st[2 * node].mod0 + st[2 * node + 1].mod0;
        st[node].mod1 = st[2 * node].mod1 + st[2 * node + 1].mod1;
        st[node].mod2 = st[2 * node].mod2 + st[2 * node + 1].mod2;
    }
}

void update_prop(int node) {
	int mod0 = st[node].mod0, mod1 = st[node].mod1, mod2 = st[node].mod2;
    st[node].mod0 = mod2;
    st[node].mod1 = mod0;
    st[node].mod2 = mod1;
}

void down(int node) { // a separate function for lazy propagation to avoid complexity
    if (st[node].lazy) {
        int val = st[node].lazy;
        st[2 * node].lazy += val;
        st[2 * node + 1].lazy += val;
        for(int i = 0; i < st[node].lazy % 3; i++) {
            update_prop(2 * node);
            update_prop(2 * node + 1);
        }
        st[node].lazy = 0;
    }
}

void update(int node, int start, int end, int l, int r) { // add all members in [l, r] by 1
    if (r < start || end < l) return;
    if (l <= start && end <= r) {
        update_prop(node);
        st[node].lazy += 1;
    }
    else {
        down(node);
        int mid = (start + end) / 2;
        update(2 * node, start, mid, l, r);
        update(2 * node + 1, mid + 1, end, l, r);
        st[node].mod0 = st[2 * node].mod0 + st[2 * node + 1].mod0;
        st[node].mod1 = st[2 * node].mod1 + st[2 * node + 1].mod1;
        st[node].mod2 = st[2 * node].mod2 + st[2 * node + 1].mod2;
    }
}

int query(int node, int start, int end, int l, int r) {
    if (r < start || end < l) return 0;
    if (l <= start && end <= r) return st[node].mod0;
    else {
        down(node);
        int mid = (start + end) / 2;
        return query(2 * node, start, mid, l, r) + query(2 * node + 1, mid + 1, end, l, r);
    }
}

void solve() {
    memset(st, 0, sizeof st);
    cin >> N >> Q;
    //for (int i = 1; i <= N; i++) cin >> arr[i];
    build(1, 1, N);
    while (Q--) {
        char c; cin >> c;
        if (c == '0') {
            int l, r; cin >> l >> r; l++; r++;
            update(1, 1, N, l, r);
        }
        else {
            int l, r; cin >> l >> r; l++; r++;
            cout << query(1, 1, N, l, r) << "\n";
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
