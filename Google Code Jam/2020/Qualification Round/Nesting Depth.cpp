#include <bits/stdc++.h>

using namespace std;

int TC;
string S;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> TC;
    for (int t = 1; t <= TC; t++) {
        cin >> S;
        string ans = "";
        int cur_left = 0;
        for (int i = 0; i < S.size(); i++) {
            int val = S[i] - '0';
            if (val > cur_left)
                for (int i = 0; i < val - cur_left; i++)
                    ans += "(";
            else
                for (int i = 0; i < cur_left - val; i++)
                    ans += ")";
            ans += S[i];
            cur_left = val;
        }
        for (int i = 0; i < cur_left; i++) ans += ")";
        cout << "Case #" << t << ": " << ans << "\n";
    }
}
