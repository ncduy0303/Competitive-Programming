// Given a string s (with length n) and a pattern p (with length m), find all occurrence of p in s
// Time complexity: O(n + m)
// Build the prefix function kmp, kmp[i] = is the maximum length of the proper suffix that is also a prefix of substring [1..i]
// Problem link: https://cses.fi/problemset/task/1753/

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e6 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

int kmp[MAX_N], num;

void kmp_preprocess(string P) {
    int i = 0, j = -1; kmp[0] = -1;
    while (i < P.size()) { 
        while (j >= 0 && P[i] != P[j]) j = kmp[j];
        i++; j++; 
        kmp[i] = j;
    }
}

void kmp_search(string S, string P) {
    int i = 0, j = 0;
    while (i < S.size()) {
        while (j >= 0 && S[i] != P[j]) j = kmp[j];
        i++; j++;
        if (j == P.size()) { // find a match at index i - j
            num++; 
            j = kmp[j]; 
        }
    }
}

void solve() {
    string s, p; cin >> s >> p;
    kmp_preprocess(p);
    kmp_search(s, p);
    cout << num << "\n";
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