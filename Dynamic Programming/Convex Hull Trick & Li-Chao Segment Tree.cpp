// Use Convex Hull Trick (CHT) to optimize a DP solution
// Alternatively, use Li-Chao Segment Tree
// Problem link: https://atcoder.jp/contests/dp/tasks/dp_z

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

struct convexhull {
    struct line {
        ll m, c; // y = m * x + c
        line() {}
        line(ll m, ll c): m(m), c(c) {}
        ll operator()(ll x) {return m * x + c;}
        ll intersect(line y) {return (y.c - c + m - y.m - 1) / (m - y.m);}
    };
    deque<pair<line,ll>> dq;
    void add(line y) {
        while (dq.size() >= 2 && dq.back().second >= dq.back().first.intersect(y)) dq.pop_back();
        if (dq.empty()) {
            dq.push_back({y, 0});
            return;
        }
        dq.push_back({y, dq.back().first.intersect(y)});
    }
    ll query(ll x) { // only works for monotonic queries
        while (dq.size() >= 2 && dq[1].second <= x) dq.pop_front(); 
        return dq[0].first(x);
    }
    // static bool cmp(pair<line,ll> a, pair<line,ll> b) {return a.second > b.second;}
    // ll query(ll x) {
    //     auto it = *lower_bound(dq.rbegin(), dq.rend(), pair<line,ll>{{0, 0}, x}, cmp);
    //     return it.first(x);
    // }
};

struct lichaotree{
    struct tdata {
        ll m, c; // y = m * x + c
        tdata() {}
        tdata(ll m, ll c): m(m), c(c) {}
        ll operator()(ll x) {return m * x + c;}
    };
    int ln(int node) {return 2 * node;}
    int rn(int node) {return 2 * node + 1;}
    int n; vector<tdata> st;
    lichaotree(int n): n(n), st(4 * n) {}
    void update(int node, int start, int end, tdata y) {
        int mid = (start + end) / 2;
        bool b1 = y(start) < st[node](start);
        bool b2 = y(mid) < st[node](mid);
        if (b2) swap(st[node], y);
        if (start + 1 == end) return;
        if (b1 != b2) update(ln(node), start, mid, y);
        else update(rn(node), mid, end, y);
    }
    ll query(int node, int start, int end, int x) {
        if (start + 1 == end) return st[node](x);
        int mid = (start + end) / 2;
        if (x < mid) return min(st[node](x), query(ln(node), start, mid, x));
        return min(st[node](x), query(rn(node), mid, end, x));
    }
    void update(tdata y) {update(1, 0, n, y);}
    ll query(int x) {return query(1, 0, n, x);}
}; 

void solve() {
    int n; ll c; cin >> n >> c;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<ll> dp(n, LINF);
    dp[0] = 0;
    convexhull cht;
    lichaotree st(1e6 + 1);
    for (int i = 1; i < n; i++) {
        // Naive O(n ^ 2) approach
        // for (int j = 0; j < i; j++) {
        //     dp[i] = min(dp[i], dp[j] + (a[i] - a[j]) * (a[i] - a[j]) + c);
        // }

        // O(nlogn) approach using CHT or Li-Chao Segment Tree
        // dp[i] = a[i] * a[i] + c + min{-2 * a[j] * a[i] + a[j] * a[j] + dp[j]}
        cht.add({- 2 * a[i - 1], a[i - 1] * a[i - 1] + dp[i - 1]});
        dp[i] = a[i] * a[i] + c + cht.query(a[i]);
        // st.update({- 2 * a[i - 1], a[i - 1] * a[i - 1] + dp[i - 1]});
        // dp[i] = a[i] * a[i] + c + st.query(a[i]);
    }
    cout << dp[n - 1] << "\n";
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