/*
Idea: just invert the original string (swap S and E)
*/

#include <bits/stdc++.h>

using namespace std;

void solve() {
    int N; string str; cin >> N >> str;
    for (int i = 0; i < str.size(); i++)
        cout << (str[i] == 'S' ? 'E' : 'S');
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int TC; cin >> TC;
    for (int t = 1; t <= TC; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
}
