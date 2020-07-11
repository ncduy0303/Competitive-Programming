// Problem 2: Overrandomized
// Idea: count the frequency of each letter appears as the leading digit (Benford's law)
// The letter with the highest frequency will be 1, and the one with the lowest will be 9
// 0 will have a 0 frequency because it cannot exist as a leading digit

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e4;

typedef long long ll;

void solve() {
    int U; cin >> U;
    string arr[MAX_N];
    int freq[26] = {0}, used[26] = {0};
    for (int i = 0; i < MAX_N; i++) {
        ll skip; cin >> skip; // not important, we only care about the first letter of the string
        cin >> arr[i];
        for (char c : arr[i]) { // this is to mark digit 0 because its frequency as a leading digit = 0
            used[c - 'A'] = 1;
        }
        freq[arr[i][0] - 'A']++; // first letter <=> leading digit
    }
    string ans = "0123456789";
    for (int i = 0; i < 26; i++) {
        if (used[i] && freq[i] == 0) {
            ans[0] = i + 'A';
            break;
        }
    }
    for (int i = 1; i < 10; i++) {
        char mx = 'A';
        for (int j = 0; j < 26; j++) {
            if (used[j] && freq[j] > freq[mx - 'A']) {
                mx = j + 'A';
            }
        }
        ans[i] = mx;
        freq[mx - 'A'] = -1;
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
