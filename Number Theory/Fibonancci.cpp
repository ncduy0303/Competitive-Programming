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
    matrix (long long a = 1, long long b = 1, long long c = 1, long long d = 0) {
        m[0][0] = a;
        m[0][1] = b;
        m[1][0] = c;
        m[1][1] = d;
    }
    matrix clone() { return matrix(m[0][0], m[0][1], m[1][0], m[1][1]); }
    matrix operator* (matrix b) {
        matrix a = (*this).clone(), o;
        o.m[0][0] = (a.m[0][0]*b.m[0][0] + a.m[0][1]*b.m[1][0]) % MOD;
        o.m[1][0] = (a.m[0][1]*b.m[0][0] + a.m[1][1]*b.m[1][0]) % MOD;
        o.m[0][1] = (a.m[0][0]*b.m[0][1] + a.m[0][1]*b.m[1][1]) % MOD;
        o.m[1][1] = (a.m[1][0]*b.m[0][1] + a.m[1][1]*b.m[1][1]) % MOD;
        return o;
    }
};

matrix qfib(int N) {
    if (N == 1) return matrix(1, 1, 1, 0);
    matrix half = qfib(N/2);
    half = half * half;
    if (N % 2 == 1) half = half * matrix(1, 1, 1, 0); // //Compensate the 'round down' of N/2 when N is odd
    return half;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
  
    int N; cin >> N;
    cout << qfib(N).m[0][1];
}
