// Policy based data structures C++ STL
// order_of_key(k): number of elements less than k
// find_by_order(k): returns the iterator of the k-th element in a set (0-index)
// Time complexity: O(logn) for both
// Problem link: https://cses.fi/problemset/task/1144

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

// 5 lines
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <class K, class V> using ordered_map = tree<K, V, less<K>, rb_tree_tag, tree_order_statistics_node_update>;

void solve() {
    int n, q; cin >> n >> q;
    int arr[n];
    ordered_set<pair<int,int>> os;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        os.insert({arr[i], i});
    }
    while (q--) {
        char c; cin >> c;
        if (c == '!') {
            int k, x; cin >> k >> x; k--;
            os.erase(os.find_by_order(os.order_of_key({arr[k], k})));
            os.insert({x, k});
            arr[k] = x;
        }
        else {
            int a, b; cin >> a >> b;
            cout << os.order_of_key({b + 1, 0}) - os.order_of_key({a, 0}) << "\n";
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