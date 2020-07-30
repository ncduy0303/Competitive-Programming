// Calculate A^B mod M;
// Time complexity: O(logB)

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

// Int Exponention (if M fits in the range of 32-bit signed integer)
int qexp(int A, int B, int M) { 
    if (B == 0) return 1; // base case A^0 = 1
    long long half = qexp(A, B/2, M);
    (half *= half) %= M;
    if (B % 2 == 1) half *= A; //Compensate the 'round down' of B/2 when B is odd
    return half % M;
}

/* Long Long Exponention (if M fits in the range of 64-bit signed integer)
long long qmult(long long A, long long B, long long M) { 
    if (B == 0) return 0; // base case A*0 = 0
    long long half = qmult(A, B/2, M);
    (half += half) %= M;
    if (B % 2 == 1) half += (A % M); // Compensate the 'round down' of B/2 when B is odd
    return half % M;
}

long long qexp(long long A, long long B, long long M) { 
    if (B == 0) return 1; //base case A^0 = 1
    long long half = qexp(A, B/2, M);
    half = qmult(half, half, M); // qmult is required to ensure this operation does not overflow
    if (B % 2 == 1) half *= (A % M); // Compensate the 'round down' of B/2 when B is odd
    return half % M;
}
*/

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int A, B, M;
    cin >> A >> B >> M;
    cout << qexp(A, B, M);
}
