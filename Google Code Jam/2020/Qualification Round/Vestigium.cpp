#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100 + 5;

int TC, N, arr[MAX_N][MAX_N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> TC;
    for (int t = 1; t <= TC; t++) {
        int num_row = 0, num_col = 0, trace = 0;
        set<int> cur;
        cin >> N;
        for (int i = 1; i <= N; i++) {
            cur.clear();
            for (int j = 1; j <= N; j++) {
                cin >> arr[i][j];
                cur.insert(arr[i][j]);
                if (i == j) trace += arr[i][j];
            }
            if (cur.size() != N) num_row++;
        }
        for (int i = 1; i <= N; i++) {
            cur.clear();
            for (int j = 1; j <= N; j++) {
                cur.insert(arr[j][i]);
            }
            if (cur.size() != N) num_col++;
        }
        cout << "Case #" << t << ": " << trace << " " << num_row << " " << num_col << "\n";
    }
}
