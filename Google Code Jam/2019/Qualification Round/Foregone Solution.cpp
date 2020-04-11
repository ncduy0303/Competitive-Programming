/*
Idea: split digit '4' into '2' + '2' and any other digit 'X' into '0' + 'X'
*/

#include <bits/stdc++.h>

using namespace std;

void solve() {
    string S; cin >> S;
    deque<int> A, B;
    for (int i = 0; i < S.size(); i++) {
        int num = S[i] - '0';
        if (num == 4) {
            A.push_back(2);
            B.push_back(2);
        }
        else {
            A.push_back(0);
            B.push_back(num);
        }
    }
    while (A.front() == 0) A.pop_front();
    for (auto x : A) cout << x;
    cout << " ";
    for (auto x : B) cout << x;
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
