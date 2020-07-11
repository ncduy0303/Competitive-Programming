/*
Given a string S (with length N) and a pattern P (with length M), find all the occurrence of P in S
Naive Approach: O(NM)
Z-algorithm Time complexity: O(N + M)
Idea: build the Z function, Z[i] = the maximum length of the common prefix of substring [i..n] and the original string [1..n]
*/

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

vector<int> Z_Func(string T) { // build the Z function of string T
    vector<int> Z(T.size());
    int l = -1, r = -1;
    Z[0] = T.size(); // base case
    for (int i = 1; i < T.size(); i++) {
        Z[i] = (i >= r) ? 0 : min(r - i, Z[i - l]);
        while (i + Z[i] < T.size() && T[i + Z[i]] == T[Z[i]]) Z[i]++;
        if (i + Z[i] > r) {
            l = i;
            r = i + Z[i];
        }
    }
    return Z;
}

void Z_Algo(string S, string P) { // use the Z function for string matching
    string T = P + "#" + S;
    vector<int> Z = Z_Func(T);
    for (int i = P.size() + 1; i < T.size(); i++)
        if (Z[i] == P.size())
            printf("P is found at index %d in S\n", i - P.size() - 1);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    string S, P; cin >> S >> P;
    Z_Algo(S, P);
}
