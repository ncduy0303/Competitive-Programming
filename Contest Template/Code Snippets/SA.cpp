#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

struct SA {
    int n, m; string s;
    vector<int> p, c, lcp, type;
    SA() : n(), m(), s() {}
    void add(string t) {
        for (int i = 0; i < t.size(); i++) type.push_back(m);
        type.push_back(-1);
        s += t;
        s += char(32 + m++);
        n = s.size();
    }
    void build_SA() { 
        p.assign(n, 0); c.assign(n, 0);
        vector<pair<char,int>> a(n);
        for (int i = 0; i < n; i++) a[i] = {s[i], i};
        sort(a.begin(), a.end());
        for (int i = 0; i < n; i++) p[i] = a[i].second;
        for (int i = 1; i < n; i++) c[p[i]] = (a[i].first == a[i - 1].first) ? c[p[i - 1]] : c[p[i - 1]] + 1;
        for (int k = 0; (1 << k) < n; k++) {
            for (int i = 0; i < n; i++) p[i] = (p[i] - (1 << k) + n) % n;
            vector<int> np(n), nc(n), cnt(n), pos(n);
            for (int x : c) cnt[x]++;
            for (int i = 1; i < n; i++) pos[i] = pos[i - 1] + cnt[i - 1];
            for (int x : p) np[pos[c[x]]++] = x;
            p = np;
            for (int i = 1; i < n; i++) {
                ar<int,2> cur = {c[p[i]], c[(p[i] + (1 << k)) % n]};
                ar<int,2> pre = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]};
                nc[p[i]] = (cur == pre) ? nc[p[i - 1]] : nc[p[i - 1]] + 1;
            }
            c = nc;
        } 
    }
    void build_LCP() {
        lcp.assign(n, 0);
        for (int i = 0, k = 0; i < n - 1; i++, k = max(k - 1, 0)) {
            int pi = c[i], j = p[pi - 1];
            while (s[i + k] == s[j + k]) k++;
            lcp[pi] = k;
        }
    }
    // print the suffix array
    void print() {
        for (int i = 0; i < n; i++) {
            cout << p[i] << " " << lcp[i] << " " << s.substr(p[i], n) << "\n";
        }
    }
    // no. of distinct substrings in s
    ll substr_cnt() { 
        ll res = 0;
        for (int i = 0; i < n; i++) 
            res += (n - p[i] - 1) - lcp[i]; 
        return res;
    }
    // no. of occurrences of t in s
    int substr_search(string t) { 
        int lo, hi, lb, ub;
        lo = 0, hi = n - 1;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (s.substr(p[mid], t.size()) >= t) hi = mid;
            else lo = mid + 1;
        }
        lb = lo;
        lo = 0, hi = n - 1;
        while (lo < hi) {
            int mid = (lo + hi + 1) / 2;
            if (s.substr(p[mid], t.size()) <= t) lo = mid;
            else hi = mid - 1;
        }
        ub = lo;
        return s.substr(p[lb], t.size()) == t ? ub - lb + 1 : 0;
    }
    // k-th lexicographically smallest substring in s
    string k_smallest(int k) {
        ll cur = 0;
        int pos = 0, len = 0;
        for (int i = 1; i < n; i++) {
            int step = n - 1 - p[i] - lcp[i];
            if (cur + step < k) cur += step;
            else {
                pos = p[i];
                len = cur + step - k;
                len = lcp[i] + step - len;
                break;
            }
        }
        return s.substr(pos, len);
    }
    // lexicographically minimal longest common substring
    string lcs() {
        if (m == 1) return s.substr(0, n - 1);
        vector<int> C(m);
        set<pair<int,int>> ms;
        pair<int,int> ans = {0, 0};
        for (int i = m, j = m, cnt = 0; j < n; i++) {
            while (cnt < m && j < n) {
                ms.insert({lcp[j], p[j]});
                if (++C[type[p[j]]] == 1) cnt++;
                j++;
            }
            if (--C[type[p[i]]] == 0) cnt--;
            ms.erase(ms.find({lcp[i], p[i]}));
            auto cur = *ms.begin();
            if (cur.first > ans.first || (cur.first == ans.first && s.substr(cur.second, cur.first) < s.substr(ans.second, ans.first))) {
                ans = cur;
            }
        }
        return s.substr(ans.second, ans.first);
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
}