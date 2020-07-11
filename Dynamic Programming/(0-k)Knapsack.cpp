/* 0-1 Knapsack Problem
Given a list of items with their weights and values
Find the maximum value one can obtain with a total weight x limit
Problem link: https://cses.fi/problemset/task/1159/
Idea: convex hull optimization
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int n, x; cin >> n >> x;
    int cost[n], val[n], copies[n];
    for (int i = 0; i < n; i++) cin >> cost[i];
    for (int i = 0; i < n; i++) cin >> val[i];
    for (int i = 0; i < n; i++) cin >> copies[i];

    vector<int> dp(n + 1);
    pair<int,int> q[x + 1];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < min(x + 1, cost[i]); j++) {
            int l = 0, r = 0;
            for (int k = j, u = k; k <= x; k += cost[i], u++) {
                pair<int,int> p(dp[k] - u * val[i], u);
                while (r > l && q[r - 1] < p) r--;
                q[r++] = p;
                if (q[l].second == u - copies[i] - 1) l++;
                dp[k] = q[l].first + u * val[i];
            }
        }
    }

    cout << *max_element(dp.begin(), dp.end());
}

