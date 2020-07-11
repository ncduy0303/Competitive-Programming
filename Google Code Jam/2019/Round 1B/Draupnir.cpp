// Problem 2: Draupnir
// Idea: Mathematical Analyzing

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

const long long mod = 1 << 7; // because 1 <= Ri <= 100 < 2^7

void solve() {
    long long R[7];
    cout << 200 << endl;
    // R1 x 2^200 + R2 x 2^100 + R3 x 2^66 + R4 x 2^50 + R5 x 2^40 + R6 x 2^33
    // mod 2^63, so it becomes R4 x 2^50 + R5 x 2^40 + R6 x 2^33
    // see that there is no overlap between R4, R5, and R6 since there power differ by at least 2^7
    long long res; cin >> res;
    R[4] = (res >> 50) % mod;
    R[5] = (res >> 40) % mod;
    R[6] = (res >> 33) % mod;

    cout << 50 << endl;
    // R1 x 2^50 + R2 x 2^25 + R3 x 2^16 + R4 x 2^12 + R5 x 2^10 + R6 x 2^8
    cin >> res;
    res -= ((R[4] << 12) + (R[5] << 10) + (R[6] << 8));
    // we already determined R4, R5, R6
    R[1] = (res >> 50) % mod;
    R[2] = (res >> 25) % mod;
    R[3] = (res>> 16) % mod;

    cout << R[1] << " " << R[2] << " " << R[3] << " " << R[4] << " " << R[5] << " " << R[6] << endl;
    cin >> res;
    assert(res == 1);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int tc, w; cin >> tc >> w;
    for (int t = 1; t <= tc; t++) {
        //cout << "Case #" << t  << ": ";
        solve();
    }
}
