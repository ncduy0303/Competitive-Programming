// Given a string s (with length n) and a pattern p (with length m), find all the occurrence of p in s
// Time complexity: O(n + m)
// Problem link: https://cses.fi/problemset/task/1753/

#include <bits/stdc++.h>
 
using namespace std;
 
#define ar array
#define ll long long
 
const int MAX_N = 1e5 + 5;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;
 
// f[i] = length of the longest common prefix between s and the substring s[i...n-1]
vector<int> z_func(string s) {
    int n = s.size();
    vector<int> f(n); // f[0] = 0 by default
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r) f[i] = min(r - i + 1, f[i - l]);
        while (i + f[i] < n && s[f[i]] == s[i + f[i]]) f[i]++;
        if (i + f[i] - 1 > r) l = i, r = i + f[i] - 1;
    }
    return f;
}
 
int cnt_occ(string s, string t) {
    string ts = t + "#" + s;
    int n = t.size(), m = s.size(), nm = ts.size();
    auto f = z_func(ts);
    int res = 0;
    for (int i = n + 1; i < nm; i++) res += (f[i] == n);
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