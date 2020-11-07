#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

template <class T> struct matrix {
    vector<vector<T>> m;
    int r, c;
    matrix() : r(), c() {}
    matrix(int r, int c, T x) : r(r), c(c), m(r, vector<T>(c, x)) {}
    matrix(int n) : matrix(n, n, 0) { // identity matrix
        for (int i = 0; i < n; i++) m[i][i] = 1;
    }
    matrix operator+ (matrix<T> b) {
        matrix<T> a = *this;
        assert(a.r == b.r); 
        assert(a.c == b.c);
        matrix<T> o(a.r, a.c, 0);
        for (int i = 0; i < a.r; i++)
            for (int j = 0; j < a.c; j++)
                    o.m[i][j] = a.m[i][j] + b.m[i][j];
        return o;
    }
    matrix operator- (matrix<T> b) {
        matrix<T> a = *this;
        assert(a.r == b.r); 
        assert(a.c == b.c);
        matrix<T> o(a.r, a.c, 0);
        for (int i = 0; i < a.r; i++)
            for (int j = 0; j < a.c; j++)
                    o.m[i][j] = a.m[i][j] - b.m[i][j];
        return o;
    }
    matrix operator* (matrix<T> b) {
        matrix<T> a = *this;
        assert(a.c == b.r);
        matrix<T> o(a.r, b.c, 0);
        for (int i = 0; i < a.r; i++)
            for (int j = 0; j < b.c; j++)
                for (int k = 0; k < a.c; k++)
                    o.m[i][j] = o.m[i][j] + a.m[i][k] * b.m[k][j];
        return o;
    }
    matrix operator^ (ll b) {
        assert(r == c);
        matrix<T> a(r, c, 0);
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                a.m[i][j] = m[i][j];
        matrix<T> o(r);
        while (b) {
            if (b % 2) o = o * a;
            a = a * a;
            b /= 2;
        }
        return o;
    }
    void print() {
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) cout << m[i][j] << " ";
            cout << "\n";
        }
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
}