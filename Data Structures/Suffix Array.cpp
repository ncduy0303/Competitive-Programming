// Suffix Array: storing all suffixes of a string, useful for many string-related problems
// Problem link: https://www.spoj.com/problems/SUBST1/

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;



void solve() {
    string s; cin >> s; s += "$";
    int n = s.size();
    vector<int> p(n), c(n);
    vector<pair<char,int>> a(n);
    for (int i = 0; i < n; i++) a[i] = {s[i], i};
    sort(a.begin(), a.end());
    for (int i = 0; i < n; i++) p[i] = a[i].second;
    for (int i = 1; i < n; i++) c[p[i]] = (a[i].first == a[i - 1].first) ? c[p[i - 1]] : c[p[i - 1]] + 1;
    for (int k = 0; (1 << k) < n; k++) {
        for (int i = 0; i < n; i++) p[i] = (p[i] - (1 << k) + n) % n;
        vector<int> np(n), nc(n), cnt(n), pos(n);
        for (int x : p) cnt[c[x]]++;
        for (int i = 1; i < n; i++) pos[i] = pos[i - 1] + cnt[i - 1];
        for (int x : p) np[pos[c[x]]++] = x;
        p = np;
        for (int i = 1; i < n; i++) {
            pair<int,int> cur = {c[p[i]], c[(p[i] + (1 << k)) % n]};
            pair<int,int> pre = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]};
            nc[p[i]] = (cur == pre) ? nc[p[i - 1]] : nc[p[i - 1]] + 1;             
        }
        c = nc;
    } 
    vector<int> lcp(n);
    for (int i = 0, k = 0; i < n - 1; i++, k = max(k - 1, 0)) {
        int pi = c[i], j = p[pi - 1];
        while (s[i + k] == s[j + k]) k++;
        lcp[pi] = k;
    }
    
    ll ans = 0;
    for (int i = 0; i < n; i++) ans += (n - p[i] - 1) - lcp[i]; 
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int tc; cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t  << ": ";
        solve();
    }
}