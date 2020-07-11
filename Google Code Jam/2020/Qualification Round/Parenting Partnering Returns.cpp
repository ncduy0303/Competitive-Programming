#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1000 + 5;

struct work {
    int l, r, id;
};

int TC, N;
work arr[MAX_N];

bool cmp (work a, work b) { // sort based on starting time
    if (a.l == b.l) return a.r < b.r;
    return a.l < b.l;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> TC;
    for (int t = 1; t <= TC; t++) {
        cin >> N;
        for (int i = 0; i < N; i++) {
            cin >> arr[i].l >> arr[i].r;
            arr[i].id = i;
        }
        sort(arr, arr + N, cmp);

        int J_end = -1, C_end = -1;
        char ans[N];
        bool valid = true;
        for (int i = 0; i < N; i++) {
            if (arr[i].l >= C_end) {
                C_end = arr[i].r;
                ans[arr[i].id] = 'C';
            }
            else if (arr[i].l >= J_end) {
                J_end = arr[i].r;
                ans[arr[i].id] = 'J';
            }
            else {
                valid = false;
                break;
            }
        }
        cout << "Case #" << t << ": ";
        if (valid) {
            for (int i = 0; i < N; i++) cout << ans[i];
        }
        else cout << "IMPOSSIBLE";
        cout << "\n";
    }
}
