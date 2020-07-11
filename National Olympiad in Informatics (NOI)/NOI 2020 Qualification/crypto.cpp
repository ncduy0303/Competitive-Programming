/* NOI 2020 Qualification: Crypto
Idea: Change the absolute values to relative order within the array => Reduce the range from 10^9 to N
To calculate the lexicographical order, start from left to right, add (N - i)! x (No.of unused smaller values than cur_value)
Here, I used C++ STL policy_based ordered set, but other data structures also works
Time complexity: O(NlogN)
*/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

const int MAX_N = 300000 + 5;
const int MAX_L = 20; // ~ Log N
const long long MOD = 1e9 + 7;
const long long INF = 1e18;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

#define LSOne(S) (S & (-S))
#define isBitSet(S, i) ((S >> i) & 1)

int N, factorial[MAX_N];

ll mod_product(ll a, ll b) {
    return ((a % MOD) * (b % MOD)) % MOD;
}

void build_table() { // pre-calculate the values of i! for all 1 <= i <= N
    ll res = 1;
    for (int i = 1; i <= N; i++) {
        res = mod_product(res, i);
        factorial[i] = res;
    }
}

void solve() {
    cin >> N;
    build_table();
    pair<ll, int> arr[N + 1];
    for (int i = 1; i <= N; i++) {
        ll x; cin >> x;
        arr[i] = {x, i};
    }
    sort(arr + 1, arr + N + 1);
    vector<ll> arr2(N + 1);
    for (int i = 1; i <= N; i++) { // absolute order -> relative order
        arr2[arr[i].second] = i;
    }
    ll ans = 1;
    ordered_set used;
    for (int i = 1; i <= N; i++) {
        ll x = arr2[i];
        ll num_smaller = used.order_of_key(x);
        ll cnt = mod_product(factorial[N - i], x - 1 - num_smaller);
        ans += cnt;
        ans %= MOD;
        used.insert(x);
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    solve();
}
