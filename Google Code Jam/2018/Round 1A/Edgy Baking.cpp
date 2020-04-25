// Problem 3: Edgy Baking
// Idea: Dynamic Programming (similar to the knapsack problem, (cut/not cut), maximizing value with a given weight)

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 60000;

void solve() {
    int N; double P;
    cin >> N >> P;
    double X[N], Y[N], sum = 0;
    for (int i = 0; i < N; i++) {
        cin >> X[i] >> Y[i];
        if (X[i] > Y[i]) swap(X[i], Y[i]);
        X[i] *= 2; Y[i] *= 2;
        sum += (X[i] + Y[i]);
        P   -= (X[i] + Y[i]);
    }
    vector<double> dp(MAX_N, -1);
    dp[0] = 0;
    for (int i = 0; i < N; i++) {
		double v = sqrt(X[i] * X[i] + Y[i] * Y[i]);
		for (int w = MAX_N - 1; w >= 0; w--) {
			if (dp[w] == -1) continue;
			dp[w + X[i]] = max(dp[w + X[i]], dp[w] + v);
		}
	}
	double ans = 0;
	for (int w = 0; w < MAX_N; w++) {
		if (w > P) break;
		if (dp[w] == -1) continue;
		ans = max(ans, dp[w]);
	}
	ans = min(ans, P);
	cout << setprecision(20) << ans + sum << "\n";
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
