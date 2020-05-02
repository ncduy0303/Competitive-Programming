// Problem 1: Robot Programming Strategy

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 5;
const int MAX_L = 20; // ~ Log N
const long long MOD = 1e9 + 7;
const long long INF = 1e18;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) (S & (-S))
#define isBitSet(S, i) ((S >> i) & 1)


void solve() {
    int N; cin >> N;
    string C[N];
    int max_len = 0;
    for (int i = 0; i < N; i++) {
        cin >> C[i];
    }
    string ans = ""; bool valid = true;
    bool defeated[N] = {false};
    for (int i = 0; i < 500 && valid; i++) {
        int mask = 0;
        for (int j = 0; j < N; j++) {
            if (defeated[j]) continue;
            int c = C[j][i % C[j].size()];
            switch(c) {
                case 'R': mask |= 1; break;
				case 'P': mask |= 2; break;
				case 'S': mask |= 4; break;
            }
        }
        if (mask == 7) valid = false;
        else if (mask == 3 || mask == 1) {
            ans += "P";
            for (int j = 0; j < N; j++)
                if (C[j][i % C[j].size()] == 'R')
                    defeated[j] = true;
        }
        else if (mask == 5 || mask == 4) {
            ans += "R";
            for (int j = 0; j < N; j++)
                if (C[j][i % C[j].size()] == 'S')
                    defeated[j] = true;
        }
        else if (mask == 6 || mask == 2) {
            ans += "S";
            for (int j = 0; j < N; j++)
                if (C[j][i % C[j].size()] == 'P')
                    defeated[j] = true;
        }
        else break;
    }
    if (valid) cout << ans << "\n";
    else cout << "IMPOSSIBLE\n";
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
