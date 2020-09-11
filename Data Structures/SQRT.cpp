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

const int SQRT = 450;

struct node{
    int l, r, id;
};
 
bool cmp(node a, node b){
    if (a.l/SQRT != b.l/SQRT)
        return a.l/SQRT < b.l/SQRT;
    else
        return a.r < b.r;
        // trick to reduce run time 
        // return (a.r < b.r) ^ ((a.l/SQRT) % 2);
}
 
int n, q, arr[MAX_N], ans[MAX_N], cnt[MAX_N], cur;
node query[MAX_N];

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
    sort(query + 1, query + n + 1, cmp);
    int curL = 0, curR = 0;
    add(0);
    for (int i = 1; i <= n; i++) {
        int L = query[i].l, R = query[i].r;
        while (curL < L) subtract(curL++);
        while (curL > L) add(--curL);
        while (curR < R) add(++curR);
        while (curR > R) subtract(curR--);
        ans[query[i].id] = cur;
    }
}

void solve() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> arr[i];
    compress();
    for (int i = 1; i <= q; i++) {
        cin >> query[i].l >> query[i].r;
        query[i].id = i;
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