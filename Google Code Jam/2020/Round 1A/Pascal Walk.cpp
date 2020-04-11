/*
Notice that the entries in the r-th row (counting starting from 1) sum to 2^r-1
=> We can represent N in binary, and then look through that representation, starting from the least significant bit
=> If the r-th least significant bit (counting starting from 1) is a 1,
   our path should consume all of the elements in the r-th row
=> However, as the path must be continuous, we may overshoot as we traveling from rows to rows, so instead of N we can
   we can find the path to reach N - 30 (as we 2^30 > 10^9) and then we can always balance back by traveling through "1" cell
*/

#include <bits/stdc++.h>

using namespace std;

void solve() {
    int N; cin >> N;
    // trivial construction for very small n
	if (N < 30) {
		for (int i = 0; i < N; i++)
			cout << i + 1 << " 1\n";
		return;
	}
    // construction for big n based on binary
    N -= 30;
    int m = 0;
	bool left = true;
    for (int i = 0; i < 30; i++) {
        // move to current row
		cout << i + 1 << " " << (left ? 1 : i + 1) << "\n";
		if (N >> i & 1) {
            if (left)
				for (int j = 1; j <= i; j++)
					cout << i + 1<< " " << j + 1 << "\n";
			else
				for (int j = i - 1; j >= 0; j--)
					cout << i + 1 << " " << j + 1 << "\n";
            left = !left;
			// add 1 to m to add the additional 1 later
			m++;
		}
    }
    // add some additional ones
	for (int i = 30; m; m--, i++) {
		// move to current row
		cout << i + 1 << " " << (left ? 1 : i + 1) << "\n";
	}
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int TC; cin >> TC;
    for (int t = 1; t <= TC; t++) {
        cout << "Case #" << t << ":\n";
        solve();
    }
}
