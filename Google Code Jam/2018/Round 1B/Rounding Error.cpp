// Problem 1: Rounding Error
// Idea: Greedy - Maximum answer is when as many of the percentages as possible are rounded up

#include <bits/stdc++.h>

void solve() {
    int n, m; cin >> n >> m;
    vector<int> arr(m);
    for (int i = 0; i < m; i++) {
        cin >> arr[i];
    }

    priority_queue<pair<int, int>> pq;
    int sum = 0;
    for (int i = 0; i < m; i++) {
        sum += arr[i];
        arr[i] = (arr[i] * 100 + (n / 2));
        pq.push({arr[i] % n, i});
    }
    for (int i = sum; i < n; i++) {
        arr.push_back(n / 2);
        pq.push({n / 2, m + i - sum});
    }

    while (sum++ < n) {
        int v = pq.top().second;
        pq.pop();
        arr[v] += 100;
        pq.push({arr[v] % n, v});
    }

    int ans = 0;
    for (int x : arr) {
        ans += x / n;
    }

    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int tc; cin >> tc;
    for (int t = 1; t <= tc; t++) {
        cout << "Case #" << t  << ": ";
        solve();
    }
}
