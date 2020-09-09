// Find the n-th Fibonacci number using matrix exponention
// Time complexity: O(logn) 
// Problem link: https://cses.fi/problemset/task/1722

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

struct matrix {
    const static int n = 2;
    ll m[n][n];
    matrix (int x = 0) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                m[i][j] = 0;
        if (x)
            for (int i = 0; i < n; i++)
                m[i][i] = x;
    }
    matrix operator* (matrix b) {
        matrix o, a = *this;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++)
                    o.m[i][j] = (o.m[i][j] + a.m[i][k] * b.m[k][j]) % MOD;
        return o;
    }
};

matrix qexp(matrix a, ll b) {
    matrix res = matrix(1); // indentity matrix
    while (b) {
        if (b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

/* 
The matrix used to find the n-th Fibonacci number looks like this:
    0 1
    1 1
*/

void solve() {
    ll n; cin >> n;
    matrix a; 
    a.m[0][1] = a.m[1][1] = a.m[1][0] = 1;
    cout << qexp(a, n + 1).m[0][0] << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int tc; tc = 1;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t  << ": ";
        solve();
    }
}