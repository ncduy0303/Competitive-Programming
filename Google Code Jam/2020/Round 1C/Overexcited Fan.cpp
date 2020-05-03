// Problem 1: Overexcited Fan
// Idea: Just check the current position of the target after each minute to see whether we can reach the location in time

#include <bits/stdc++.h>

using namespace std;

void solve() {
    int xn, yn;
    string str;
    cin >> xn >> yn >> str;
    for (int t = 0; t < str.size(); t++) {
        char c = str[t];
        if (c == 'N') yn++;
        if (c == 'S') yn--;
        if (c == 'W') xn--;
        if (c == 'E') xn++;
        if (abs(xn) + abs(yn) <= t + 1) {
            cout << t + 1 << "\n";
            return;
        }
    }
    cout << "IMPOSSIBLE" << "\n";
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
