/* NOI 2020 Qualification: Fuel Station
Idea: First sort the fuel stations from nearest to farthest from the starting point

Key observation:
MinF must be between 0 and D.
If tbere are no Bi values, F + 1 will works if F works => Monotonic function => Can use binary search to find MinF.
With Bi values, sort all the Bi values into B1, B2, ..., Bn, and do binary search on the range [0, B1], [B1, B2], ..., [Bn, D]
The first value that can get us to D will be MinF

Time complexity: O(NlogN)
*/

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 300000 + 5;
const int MAX_L = 20; // ~ Log N
const long long MOD = 1e9 + 7;
const long long INF = 1e18;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) (S & (-S))
#define isBitSet(S, i) ((S >> i) & 1)

ll N, D;
pair<ll, pair<ll, ll>> arr[MAX_N];
set<ll> arrB;

bool valid(int mid) { // O(N)
    ll pos = 0, cur_fuel = mid;
    for (int i = 0; i < N; i++) {
        ll X = arr[i].first, A = arr[i].second.first, B = arr[i].second.second;
        if (X - pos > cur_fuel) return false;
        cur_fuel -= (X - pos);
        pos = X;
        if (mid <= B) cur_fuel += A;
    }
    if (D - pos > cur_fuel)
        return false;
    else
        return true;
}

void solve() {
    cin >> N >> D;
    for (int i = 0; i < N; i++) {
        ll X, A, B; cin >> X >> A >> B;
        arrB.insert(B);
        arr[i] = {X, {A, B}};
    }
    sort(arr, arr + N);
    ll ans = D;
    ll pre = 0;
    for (ll cur : arrB) { // O(N) => Worse case is O(N^2logN), but on average it should be O(NlogN)
        ll lo = pre;
        ll hi = cur;
        while (lo < hi) { // O(logN)
            ll mid = (lo + hi) / 2;
            if (valid(mid)) hi = mid; // O(N)
            else lo = mid + 1;
        }
        if (valid(hi)) { // First F that satisfies => Also MinF, because we are search from left to right
            ans = hi;
            break;
        }
        pre = cur;
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
