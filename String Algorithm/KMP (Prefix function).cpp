/*
Given a string S (with length N) and a pattern P (with length M), find all the occurrence of P in S
Naive Approach: O(NM)
KMP Time complexity: O(N + M)
Idea: build the prefix function kmp, kmp[i] = is the maximum length of the proper suffix that is also a prefix of substring [1..i]
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

int kmp[MAX_N];

void kmp_preprocess(string P) {
    int i = 0, j = -1; kmp[0] = -1;
    while (i < P.size()) { // pre-process the pattern string P
        while (j >= 0 && P[i] != P[j]) j = kmp[j];// if different, reset j using kmp array
        i++; j++; // if same, advance both pointers
        kmp[i] = j;
    }
}

void kmp_search(string S, string P) {
    int i = 0, j = 0;
    while (i < S.size()) {
        while (j >= 0 && S[i] != P[j]) j = kmp[j];
        i++; j++;
        if (j == P.size()) { //find a match
            printf("P is found at index %d in S\n", i - j);
            j = kmp[j]; // prepare j for the next possible match
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    string S, P; cin >> S >> P;
    kmp_preprocess(P);
    kmp_search(S, P);
}
