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

const int MAX_N = 1e5 + 5;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rand(ll l, ll r) {return uniform_int_distribution(l, r)(rng);}
const int BASE = rand(300, 1e9);
const int NUM_MOD = 2;
const ll MODS[] = {(int)1e9 + 2277, (int)1e9 + 5277};
struct Hash {
    vector<ll> H[NUM_MOD], P[NUM_MOD];
    Hash(string s) {
        for (int i = 0; i < NUM_MOD; i++) {
            P[i].push_back(1);
            H[i].push_back(0);
        }
        for (char c : s) {
            for (int i = 0; i < NUM_MOD; i++) {
                P[i].push_back(P[i].back() * BASE % MODS[i]);
                H[i].push_back((H[i].back() * BASE + c) % MODS[i]);
            }
        }
    } 
    ar<ll,NUM_MOD> operator()(int l, int r) {
        ar<ll,NUM_MOD> res;
        for (int i = 0; i < NUM_MOD; i++) {
            res[i] = (H[i][r + 1] - H[i][l] * P[i][r + 1 - l]) % MODS[i];
            if (res[i] < 0) res[i] += MODS[i];
        }
        return res;
    }
};

int cnt_occ(string s, string t) {
    int n = s.size(), m = t.size();
    Hash hs(s), ht(t);
    int res = 0;
    for (int i = 0, j = m - 1; j < n; i++, j++) {
        res += (hs(i, j) == ht(0, m - 1));
    }
    return res;
}

void solve() {
    string s, t; cin >> s >> t;
    cout << cnt_occ(s, t) << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int tc = 1;
    // cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t << ": ";
        solve();
    }
}