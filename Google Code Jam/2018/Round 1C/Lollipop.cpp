// Problem 2: Lollipop
// Idea: Always try to sell the least popular lollipop so far to a customer

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 5;
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
    int likes[N] = {0}, sold[N] = {0};
    for (int i = 0; i < N; i++) {
        int D; cin >> D;
        if (D == 0) {
            cout << -1 << endl;
        }
        else {
            int cur[D];
            for (int j = 0; j < D; j++) {
                cin >> cur[j];
                likes[cur[j]]++;
            }
            int best = cur[0];
            for (int j = 0; j < D; j++) {
                if (sold[best] || (!sold[cur[j]] && likes[cur[j]] < likes[best])) {
                    best = cur[j];
                }
            }
            if (sold[best]) cout << -1 << endl;
            else cout << best << endl;
            sold[best] = 1;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int tc; cin >> tc;
    for (int t = 1; t <= tc; t++) {
        //cout << "Case #" << t  << ": ";
        solve();
    }
}
