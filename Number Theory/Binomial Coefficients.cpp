// Basically, use DP to generate C(n, k)

// If you need to calculate a lot of C(n, k) for all values n <= some constant,
// simulate Pascal Triangle and save all values into a 2D array => Time complexity: O(n^2)
// This usually serves as an intermediate step for a more difficult DP problem

// If you only need to calculate C(n, k) for a few times,
// just apply the formula directly C(n, k) = n!/(k!(n-k)!) with time complexity O(k) per query
// If you want to achieve a time complexity of O(1) per query, you can precompute all the factorials and modular inverse beforehand

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

void pascal(int n) {
    int C[n + 1][n + 1];
    for (int i = 1; i <= n; i++) C[0][i] = 0; // C(0, i) = 0
    for (int i = 0; i <= n; i++) C[i][0] = 1; // C(i, 0) = 1

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            C[i][i] = C[i - 1][j - 1] + C[i - 1][j]; // Pascal Triangle: C(i, j) = C(i - 1, j - 1) + C(i - 1, j)
}

int coefficient(int n, int k) { // Calculate nCk
    int res = 1;
    k = min(k, n - k); // as C(n, k) = C(n, n - k)
    for (int i = 0; i < k; i++) {
        res *= (n - i);
        res /= (i + 1);
    }
    return res;
}

long long qexp(long long A, long long B, long long M) { // calculate (A ^ B) % M
    if (B == 0) return 1; //base case A^0 = 1
    long long half = qexp(A, B/2, M);
    half *= half;
    half %= M;
    if (B % 2 == 1) half *= A;  //Compensate the 'round down' of B/2 when B is odd
    return half % M;
}

long long fact[MAX_N], invf[MAX_N];

void precompute() {
    fact[0] = invf[0] = 1;
    for (int i = 1; i < MAX_N; i++) {
		fact[i] = fact[i - 1] * i % MOD;
		invf[i] = qexp(fact[i], MOD - 2, MOD);
	}
}

long long coefficient2(int n, int k) { // Calculate nCk using precomputed table
    if (k < 0 || k > n) return 0;
	return fact[n] * invf[k] % MOD * invf[n - k] % MOD;
}

// A trick to calculate large factorial without overflowing is to take log at every step when precompute and take exponential when calculating
// no need for invf now because it is the same as negative log of fact
double log_fact[MAX_N];
void precompute_log() {
    log_fact[0] = 0.0; // log(0!) = 0
    for (int i = 1; i < MAX_N; i++)
        log_fact[i] = log_fact[i - 1] + log(i); // log(i!) = log((i-1)!) + log(i)
}

long long log_nCk(int n, int k) { // remember to take exponential at the end
    if (k < 0 || k > n) return 0;
	return exp(log_fact[n] - log_fact[n - k] - log_fact[k]);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int n, k; cin >> n >> k;
    cout << coefficient(n, k) << "\n";

    precompute();
    cout << coefficient2(n, k);

    /*
    Example input: 120 5
    Expected output:
    190578024
    190578024
    */
}
