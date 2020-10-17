// Mo's Algorithm for answering offline queries
// Time complexity: O(n*sqrt(n))
// Problem link: https://cses.fi/problemset/task/1734

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 2e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

struct query{
    int SQRT = 500;
    int l, r, id;
    bool operator< (query b) {
        query a = *this;
        return ar<int,2>{a.l/SQRT, a.r} < ar<int,2>{b.l/SQRT, b.r};
    }
};

int n, q, arr[MAX_N], ans[MAX_N], cnt[MAX_N], cur;
query qs[MAX_N];

void add(int idx) {
    if (cnt[arr[idx]] == 0) cur++;
    cnt[arr[idx]]++;
}
 
void subtract(int idx) {
    if (cnt[arr[idx]] == 1) cur--;
    cnt[arr[idx]]--;
}

// compress used values from 1e9 to 2e5 
void compress() {
    map<int, int> mp;
    for (int i = 1; i <= n; i++) 
        mp[arr[i]] = i;
    for (int i = 1; i <= n; i++) 
        arr[i] = mp[arr[i]];
}

void mo_algo() {
    sort(qs + 1, qs + n + 1);
    int curL = 0, curR = 0;
    add(0);
    for (int i = 1; i <= n; i++) {
        int L = qs[i].l, R = qs[i].r;
        while (curL < L) subtract(curL++);
        while (curL > L) add(--curL);
        while (curR < R) add(++curR);
        while (curR > R) subtract(curR--);
        ans[qs[i].id] = cur;
    }
}

void solve() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> arr[i];
    compress();
    for (int i = 1; i <= q; i++) {
        cin >> qs[i].l >> qs[i].r;
        qs[i].id = i;
    }
    mo_algo();
    for (int i = 1; i <= q; i++) 
        cout << ans[i] << "\n";
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