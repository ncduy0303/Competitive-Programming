// Find the N-th Fibonacci number using matrix exponention
// Time complexity: O(logN) instead of naive DP approach O(N)

#include <bits/stdc++.h>

using namespace std;

const int INF = 1 << 30;
const int MAX_N = 100000 + 5;
const int MAX_L = 20; // ~ Log N
const long long MOD = 1e9 + 7;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) (S & (-S))
#define isBitSet(S, i) ((S >> i) & 1)

struct matrix {
    long long m[2][2];
    matrix (long long a = 0, long long b = 0, long long c = 0, long long d = 0) {
        m[0][0] = a;
        m[0][1] = b;
        m[1][0] = c;
        m[1][1] = d;
    }
    matrix operator* (matrix b) {
        matrix o, a = (*this);
        o.m[0][0] = (a.m[0][0]*b.m[0][0] + a.m[0][1]*b.m[1][0]) % MOD;
        o.m[1][0] = (a.m[0][1]*b.m[0][0] + a.m[1][1]*b.m[1][0]) % MOD;
        o.m[0][1] = (a.m[0][0]*b.m[0][1] + a.m[0][1]*b.m[1][1]) % MOD;
        o.m[1][1] = (a.m[1][0]*b.m[0][1] + a.m[1][1]*b.m[1][1]) % MOD;

        // Another way to implement matrix multiplication
        // for (int i = 0; i < 2; i++) 
        //     for (int j = 0; j < 2; j++)
        //         for (int k = 0; k < 2; k++)
        //             (o.m[i][j] += (a.m[i][k] + b.m[k][j])) %= MOD; 
        return o;
    }
};

// Matrix Exponention 
matrix qexp(matrix A, int B) { 
    if (B == 1) return matrix(1, 1, 1, 0); // base case
    matrix half = qexp(A, B/2);
    half = half * half;
    if (B % 2) half = half * A; // Compensate the 'round down' of B/2 when B is odd
    return half;
}

matrix qfib(int N) {
    matrix A = matrix(1, 1, 1, 0);
    return qexp(A, N);
}

// Another implementation using C++ STL vector
vector<long long> fibo(int N) {
    if (N == 1) return {0, 1, 1, 1}; // base case
    vector<long long> mx = fibo(N / 2);
    mx = {((mx[0] * mx[0]) % MOD + (mx[1] * mx[2]) % MOD) % MOD,
          ((mx[0] * mx[1]) % MOD + (mx[1] * mx[3]) % MOD) % MOD,
          ((mx[2] * mx[0]) % MOD + (mx[3] * mx[2]) % MOD) % MOD,
          ((mx[2] * mx[1]) % MOD + (mx[3] * mx[3]) % MOD) % MOD};
    if (N % 2) mx = {mx[1], (mx[0] + mx[1]) % MOD, mx[3], (mx[2] + mx[3]) % MOD}; // Compensate the 'round down' of N/2 when N is odd
    return mx;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
  
    int N; cin >> N;
    cout << qfib(N).m[0][1] << "\n";
    cout << fibo(N + 1)[0] << "\n";
}
