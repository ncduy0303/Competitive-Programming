// Problem 3: Fair Fight
// Idea: Binary search and Sparse table

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

int n, k;
int a[MAX_N], b[MAX_N];
int st_a[MAX_N][MAX_L], st_b[MAX_N][MAX_L]; // sparse table for both arrays

long long calc() { // Sparse table for max range query
    for (int i = 1; i <= n; i++) {
        st_a[i][0] = a[i];
        st_b[i][0] = b[i];
    }
    for (int j = 1; j < MAX_L; j++) {
        for (int i = 1; i + (1 << j) <= n + 1; i++) {
            st_a[i][j] = max(st_a[i][j - 1], st_a[i + (1 << (j - 1))][j - 1]);
            st_b[i][j] = max(st_b[i][j - 1], st_b[i + (1 << (j - 1))][j - 1]);
        }
    }

    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] >= b[i]) continue;
        // Binary search to find the extreme left and extreme right
        int l = i, r = i;
        for (int j = MAX_L - 1; j >= 0; j--) {
            if (l - (1 << j) > 0 && st_b[l - (1 << j)][j] < b[i] && st_a[l - (1 << j)][j] < b[i]) {
                l -= 1 << j;
            }
        }
        for (int j = MAX_L - 1; j >= 0; j--) {
            if (r + (1 << j) <= n && st_b[r + 1][j] <= b[i] && st_a[r + 1][j] < b[i]) {
                r += 1 << j;
            }
        }
        ans += 1LL * (i - l + 1) * (r - i + 1);
    }
    return ans;
}

void solve() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] += k;
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }

    long long ans = 1LL * n * (n + 1) / 2;
    ans -= calc();

    for (int i = 1; i <= n; i++) {
        a[i] -= k; b[i] += k;
        swap(a[i], b[i]);
    }
    ans -= calc();
    cout << ans << "\n";
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
