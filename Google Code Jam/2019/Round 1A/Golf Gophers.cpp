/* Problem 2: Golf Gophers
Idea: Notice that setting all the blades with the same number helps us determine the modulo of the number of golfers with our chosen number
If we choose 7 different numbers such that their LCM >= 10e6, we will able to determine the exact value of the number of golfers
*/

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
    int cnt[MAX_N] = {0};
    for (int x : {5, 7, 9, 11, 13, 16, 17}) {
        for (int i = 0; i < 18; i++) {
            if (i > 0) cout << " ";
            cout << x;
        }
        cout << endl;
        int sum = 0;
        for (int i = 0; i < 18; i++) {
            int mod; cin >> mod;
            sum = (sum + mod) % x;
        }
        for (int i = sum; i < MAX_N; i += x) {
           cnt[i]++;
        }
    }

    for (int i = 1; i < MAX_N; i++) {
        if (cnt[i] == 7) {
            cout << i << endl;
            int res; cin >> res;
            assert(res == 1);
            break;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int tc, n, m; cin >> tc >> n >> m;
    for (int t = 1; t <= tc; t++) {
        //cout << "Case #" << t  << ": ";
        solve();
    }
}
