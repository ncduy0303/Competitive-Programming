// Create something similar to PBDS using Fenwick Tree
// Time complexity: O(logn) for both operations
// Problem link: https://cses.fi/problemset/task/1144

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 2e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

const int MAX_L = 18;

#define LSOne(S) ((S) & (-S))

int n, q, ft[MAX_N];

void update(int x, int v) {
    for (; x <= n; x += LSOne(x))
        ft[x] += v;
}

int sum(int x) {
    int res = 0;
    for (; x; x -= LSOne(x))
        res += ft[x];
    return res;
}

// using binary lifting technique
int find_by_order(int k) { 
    int sum = 0, pos = 0;
    for (int i = MAX_L; i >= 0; i--) {
        if (pos + (1 << i) < n && sum + ft[pos + (1 << i)] < k) {
            sum += ft[pos + (1 << i)];
            pos += (1 << i);
        }
    }
    return pos + 1; 
    // +1 because 'pos' will have position of largest value less than 'k'
    // this function returns 1 if k < 1 and returns N if k > N
}

int order_of_key(int k) {
    return sum(k);
}

void solve() {
    cin >> n >> q;
    int arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        update(arr[i], 1);
    }
    while (q--) {
        char c; cin >> c;
        if (c == '!') {
            int k, x; cin >> k >> x; k--;
            update(find_by_order(order_of_key(arr[k])), -1);
            update(x, 1);
            arr[k] = x;
        }
        else {
            int a, b; cin >> a >> b;
            cout << order_of_key(b + 1) - order_of_key(a) << "\n";
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