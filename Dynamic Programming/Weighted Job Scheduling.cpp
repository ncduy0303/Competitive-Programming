// Problem: Weighted Job Scheduling (given a list of jobs with start time, end time, and profit) find the maximum profit
// Link: https://dunjudge.me/analysis/problems/414/
// Time complexity: O(nlogn)

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 5;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;

int n, dp[MAX_N];
pair<ii, int> arr[MAX_N];

int bin_search(int idx) {
    int lo = 0, hi = idx -1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (arr[mid].first.first < arr[idx].first.second) { // mid ending time <= idx starting time
            if (arr[mid + 1].first.first < arr[idx].first.second)
                lo = mid + 1;
            else
                return mid;
        }
        else hi = mid - 1;
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> arr[i].first.second >> arr[i].first.first >> arr[i].second;
    sort(arr, arr + n); // based on ending time

    // dp[i] = maximum profit using the first i jobs
    memset(dp, 0, sizeof dp);
    dp[0] = arr[0].second; // based case
    for (int i = 1; i < n; i++) {
        int cur = arr[i].second;
        // use binary search to find the best position to include job i
        int idx = bin_search(i);
        if (idx != -1) cur += dp[idx];
        dp[i] = max(dp[i - 1], cur);
    }
    cout << dp[n - 1];
}
