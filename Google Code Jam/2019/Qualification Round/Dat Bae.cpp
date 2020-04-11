#include <bits/stdc++.h>

using namespace std;

string guess(int N, int B, int block) {
    string str(N, ' ');
    for (int i = 0; i < N; i++)
        str[i] = ((i / block) % 2 == 0) ? '0' : '1';
    cout << str << endl;
    string res; cin >> res;
    return res;
}

void solve() {
    int N, B, F; cin >> N >> B >> F;
    string str(N, ' ');
    for (int i = 0; i < N; i++)
        str[i] = ((i / 16) % 2 == 0) ? '0' : '1';
    string A1 = guess(N, B, 1);
    string A2 = guess(N, B, 2);
    string A4 = guess(N, B, 4);
    string A8 = guess(N, B, 8);
    vector<int> bad;
    int start = 0;
    for (int i = 0; i < N - B; i++) {
        int mod16 = (A8[i] == '1' ? 8 : 0) + (A4[i] == '1' ? 4 : 0) + (A2[i] == '1' ? 2 : 0) + (A1[i] == '1' ? 1 : 0);
        while (start % 16 != mod16) {
            bad.push_back(start);
            start++;
        }
        start++;
    }
    while (start < N) {
        bad.push_back(start);
        start++;
    }
    stringstream ss;
    for (int i = 0; i < bad.size(); i++) {
        ss << bad[i];
        if (i < bad.size() - 1) ss << " ";
    }
    cout << ss.str() << endl;
    int verdict; cin >> verdict;
    assert(verdict == 1);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int TC; cin >> TC;
    for (int t = 1; t <= TC; t++) {
        solve();
    }
}
