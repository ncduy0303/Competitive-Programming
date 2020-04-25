// Problem 1: Waffle Choppers
// Idea: Greedy, running cumulative sum horizontally and vertically
// Remember to double check the number of chips in each pieces at the end

#include <bits/stdc++.h>

using namespace std;

void solve() {
    int R, C, H, V; cin >> R >> C >> H >> V;
    int ps[R + 1][C + 1];
    memset(ps, 0, sizeof ps);
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            char c; cin >> c;
            ps[i][j] = ps[i][j - 1] + ps[i - 1][j] - ps[i - 1][j - 1] + (int)(c == '@');
        }
    }
    // Checking the entire cumulative
    if (ps[R][C] % ((H + 1) * (V + 1)) != 0 || ps[R][C] % (H + 1) != 0 || ps[R][C] % (V + 1) != 0) {
        cout << "IMPOSSIBLE\n";
        return;
    }
    // Checking the cumulative horizontal sum
    int sum_r = ps[R][C] / (H + 1);
    int cur_sum = sum_r;
    vector<int> r_cuts;
    r_cuts.push_back(0);
    for (int i = 1; i <= R; i++) {
        if (ps[i][C] > cur_sum) {
            cout << "IMPOSSIBLE\n";
            return;
        }
        else if (ps[i][C] == cur_sum) {
            cur_sum += sum_r;
            r_cuts.push_back(i);
        }
    }
    // Checking the cumulative vertical sum
    int sum_c = ps[R][C] / (V + 1);
    cur_sum = sum_c;
    vector<int> c_cuts;
    c_cuts.push_back(0);
    for (int i = 1; i <= C; i++) {
        if (ps[R][i] > cur_sum) {
            cout << "IMPOSSIBLE\n";
            return;
        }
        else if (ps[R][i] == cur_sum) {
            cur_sum += sum_c;
            c_cuts.push_back(i);
        }
    }
    // Checking each individual piece
    int sum_each = ps[R][C] / ((H + 1) * (V + 1));
    for (int i = 1; i <= H + 1; i++) {
        for (int j = 1; j <= V + 1; j++) {
            int r2 = r_cuts[i], r1 = r_cuts[i - 1];
            int c2 = c_cuts[j], c1 = c_cuts[j - 1];
            cur_sum = ps[r2][c2] + ps[r1][c1] - ps[r1][c2] - ps[r2][c1];
            if (cur_sum != sum_each) {
                cout << "IMPOSSIBLE\n";
                return;
            }
        }
    }
    cout << "POSSIBLE\n";
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
