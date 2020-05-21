/* Meet in the middle
Problem: Given an array of n numbers (n <= 40), count the number of subsets with sum x (x <= 10^9)
Link: https://cses.fi/problemset/task/1628/

Analysis:
Normally, if (n, x <= 10^6), we can do a DP knapsack with O(nx) time complexity
But as x <= 10^9, we cannot hold such a huge array, so DP is not possible

Notice that n is small (<= 40), maybe we can do some brute force
However, generating all possible subsets with lead to a O(2^n) time complexity, which is too slow

Using the meet in the middle technique, we can cut down a O(2^n) time complexity to O(2^(n/2)), which is fast enough
Idea: divide the given array into 2 sets, generate all possible subsets in each set => 2 * O(2^(n/2)) time complexity
Iterating through all possible values in one set and use binary search on the other set to find the complement to get a total sum of x
*/

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 5;
const int MAX_L = 20;
const long long MOD = 1e9 + 7;
const long long INF = 1e18 + 7;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;



int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int n; ll x; cin >> n >> x;
    int arr1[n / 2], arr2[n - n / 2];
    for (int i = 0; i < n / 2; i++) cin >> arr1[i];
    for (int i = 0; i < n - n / 2; i++) cin >> arr2[i];
    vector<ll> sum1, sum2;
    for (int i = 0; i < (1 << n / 2); i++) { // iterating through all subsets
        ll cur = 0;
        for (int j = 0; j < n / 2; j++)
            if (i & (1 << j))
                cur += arr1[j];
        sum1.push_back(cur);
    }
    for (int i = 0; i < (1 << (n - n / 2)); i++) { // iterating through all subsets
        ll cur = 0;
        for (int j = 0; j < (n - n / 2); j++)
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
