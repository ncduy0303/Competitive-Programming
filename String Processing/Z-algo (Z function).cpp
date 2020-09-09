// Given a string s (with length n) and a pattern p (with length m), find all the occurrence of p in s
// Time complexity: O(n + m)
// Build the Z function, Z[i] = the maximum length of the common prefix of substring [i..n] and the original string [1..n]
// Problem link: https://cses.fi/problemset/task/1753/

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

int num;
vector<int> Z;

vector<int> Z_Func(string t) { 
    vector<int> Z(t.size());
    int l = -1, r = -1;
    Z[0] = t.size(); 
    for (int i = 1; i < t.size(); i++) {
        Z[i] = (i >= r) ? 0 : min(r - i, Z[i - l]);
        while (i + Z[i] < t.size() && t[i + Z[i]] == t[Z[i]]) Z[i]++;
        if (i + Z[i] > r) {
            l = i;
            r = i + Z[i];
        }
    }
    return Z;
}

void Z_Algo(string s, string p) { 
    string t = p + "#" + s;
    Z = Z_Func(t);
    for (int i = p.size() + 1; i < t.size(); i++)
        if (Z[i] == p.size()) // find a match at index i - p.size() - 1
            num++;
}

void solve() {
    string s, p; cin >> s >> p;
    Z_Algo(s, p);
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