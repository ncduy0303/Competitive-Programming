// Problem 1: Manhattan Crepe Cart
// Idea: Notice that the 2 dimensions are independent, and valid coordinates are limited by P, not Q

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
    int P, Q; cin >> P >> Q;
    map<int, int> X, Y;
    for (int i = 0; i < P; i++) {
        int x, y; char c;
        cin >> x >> y >> c;
        if (c == 'E') X[x + 1]++;
        if (c == 'W') X[x]--;
        if (c == 'N') Y[y + 1]++;
        if (c == 'S') Y[y]--;
    }

    int xn = 0, cur = 0, mx = 0;
    for (auto x : X) {
        cur += x.second;
        if (cur > mx) {
            mx = cur;
            xn = x.first;
        }
    }
    int yn = 0; cur = 0, mx = 0;
    for (auto y : Y) {
        cur += y.second;
        if (cur > mx) {
            mx = cur;
            yn = y.first;
        }
    }
    cout << xn << " " << yn << "\n";
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
