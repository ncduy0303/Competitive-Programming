// Problem 2: Mysterious Road Signs
// Idea: 2 pointers to maintain the N-candidates and the M-candidates
// Time complexity: O(N)

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
    int n; cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        a[i] = x + y;
        b[i] = x - z;
    }
    map<int, int> ma, mb;
    map<pair<int, int>, int> mab;
    int j = 0;
    int last_a = -1, last_b = -1;
    int ans = -1, ways = -1, cnt = 0;
    for (int i = 0; i < n; i++) {
        ma[a[i]]++;
        mb[b[i]]++;
        mab[{a[i], b[i]}]++;
        if (i > 0 && a[i] != a[i - 1]) {
            last_a = i - 1;
        }
        if (i > 0 && b[i] != b[i - 1]) {
            last_b = i - 1;
        }
        while (j <= i) {
            if (last_a < j || last_b < j) {
                break;
            }
            cnt = ma[a[i]] + mb[b[last_a]] - mab[{a[i], b[last_a]}];
            if (cnt == i - j + 1) {
                break;
            }
            cnt = ma[a[last_b]] + mb[b[i]] - mab[{a[last_b], b[i]}];
            if (cnt == i - j + 1) {
                break;
            }
            // Impossible to move the i-pointer forward without moving the j-pointer forward
            ma[a[j]]--;
            mb[b[j]]--;
            mab[{a[j], b[j]}]--;
            j++;
        }
        int len = i - j + 1;
        if (len > ans) {
            ans = len;
            ways = 0;
        }
        if (len == ans) ways++;
    }
    cout << ans << " " << ways << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int tc; cin >> tc;
    for (int t = 1; t <= tc; t++) {
        cout << "Case #" << t  << ": ";
        solve();
    }
}
