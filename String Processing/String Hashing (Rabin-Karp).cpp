// String Hashing 
// Consider carefully the choice of 'base' and 'mod'
// 'base' should be greater than the number of characters in the input alphabet 
// 'mod' should be a large prime like 1e9 + 7

// should always convert 'a' into 1 instead 0
// should randomise the value of 'base' to avoid hacking
// should use > 1 'base' to reduce collision rate

// Example of using Hashing for String Matching (Rabin-Karp)
// Problem link: https://cses.fi/problemset/task/1753

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e6 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

const int nbase = 2;

ll P[nbase][MAX_N], H[nbase][MAX_N], B[nbase];
vector<ll> Hp(nbase);
// only need to store the hash value for the whole string p

// here use 0-index, return hase value of s[l..r]
vector<ll> gethash(int l, int r) {
    vector<ll> res;
    for (int i = 0; i < nbase; i++)
        res.push_back((H[i][r + 1] - H[i][l] * P[i][r + 1 - l] + (ll)MOD * MOD) % MOD); 
    return res;
}

void solve() {   
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    for (int i = 0; i < nbase; i++) B[i] = rng() % 100000000 + 256;

    string s, p; cin >> s >> p;
    for (int i = 0; i < nbase; i++) {
        P[i][0] = 1;
        for (int j = 0; j < s.size(); j++) {
            P[i][j + 1] = P[i][j] * B[i] % MOD;
            H[i][j + 1] = (H[i][j] * B[i] + s[j] - 'a' + 1) % MOD; 
        }
        for (int j = 0; j < p.size(); j++) {
            Hp[i] = (Hp[i] * B[i] + p[j] - 'a' + 1) % MOD; 
        }
    }

    int num = 0;
    for (int i = 0, j = i + p.size() - 1; j < s.size(); i++, j++) {
        num += (gethash(i, j) == Hp);
    }
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