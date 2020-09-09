// Given an array of n numbers (n <= 40), count the number of subsets with sum x (x <= 10^9)
// Problem link: https://cses.fi/problemset/task/1628/

/*
As x <= 10^9, DP is not possible

As n <= 40, some brute force is possible
However, generating all subsets results in O(2^n) time complexity => TLE

"Meet in the middle" technique can speed up from O(2^n) to O(2^(n/2)) => AC

Divide the array into 2 sets, generate all possible subsets in each set 
Iterating through all values in one set and use binary search on the other set to find the complement to get a total sum of x
Time complexity: 2 * O(2^(n/2))
*/

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;



void solve() {
    int n, x; cin >> n >> x;
    int m1 = n / 2, m2 = n - m1;
    int arr1[m1], arr2[m2];
    for (int i = 0; i < m1; i++) cin >> arr1[i];
    for (int i = 0; i < m2; i++) cin >> arr2[i];

    vector<ll> sum1, sum2;
    for (int i = 0; i < (1 << m1); i++) { 
        ll cur = 0;
        for (int j = 0; j < m1; j++)
            if (i & (1 << j))
                cur += arr1[j];
        sum1.push_back(cur);
    }
    for (int i = 0; i < (1 << m2); i++) { 
        ll cur = 0;
        for (int j = 0; j < m2; j++)
            if (i & (1 << j))
                cur += arr2[j];
        sum2.push_back(cur);
    }
    sort(sum1.begin(), sum1.end());
    sort(sum2.begin(), sum2.end());

    ll ans = 0;
    for (ll s1 : sum1)
        ans += upper_bound(sum2.begin(), sum2.end(), x - s1) - lower_bound(sum2.begin(), sum2.end(), x - s1);
    cout << ans;
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