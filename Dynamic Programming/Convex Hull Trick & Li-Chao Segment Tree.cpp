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

struct lichaotree {
    struct line {
        ll m, c;
        line(ll m, ll c): m(m), c(c) {}
        ll operator()(ll x) {return m * x + c;}
    };
    struct tdata {
        line seg;
        tdata *ln, *rn;
        tdata(line seg): seg(seg) {}
    };
    int n; tdata *st;
    lichaotree(int n): n(n) {st = new tdata({INF, INF});}
    void update(tdata *node, int start, int end, line y) {
        int mid = (start + end) / 2;
        bool b1 = y(start) < node->seg(start);
        bool b2 = y(mid) < node->seg(mid);
        if (b2) swap(node->seg, y);
        if (start + 1 == end) return;
        if (b1 != b2) {
            if (node->ln) update(node->ln, start, mid, y);
            else node->ln = new tdata(y);
        }
        else {
            if (node->rn) update(node->rn, mid, end, y);
            else node->rn = new tdata(y);
        }
    }
    ll query(tdata *node, ll start, ll end, ll x) {
        if (start + 1 == end) return node->seg(x);
        ll mid = (start + end) / 2;
        if (x < mid && node->ln) return min(node->seg(x), query(node->ln, start, mid, x));
        else if (node->rn) return min(node->seg(x), query(node->rn, mid, end, x));
        return node->seg(x);
    }
    void update(line y) {update(st, 0, n, y);}
    ll query(int x) {return query(st, 0, n, x);}
}; 

struct convexhull {
    struct line {
        ll m, c; 
        line(ll m, ll c): m(m), c(c) {}
        ll operator()(ll x) {return m * x + c;}
    };
    deque<line> dq;
    bool check(line p1, line p2, line p3) {
        return (p2.m - p1.m) * (p3.c - p2.c) >= (p3.m - p2.m) * (p2.c - p1.c);
    }
    void add(line y) { // decreasing slope
        while (dq.size() >= 2 && check(dq[dq.size() - 2], dq[dq.size() - 1], y)) dq.pop_back();
        dq.push_back(y);
    }
    ll query(ll x) { // min query, increasing x
        while (dq.size() >= 2 && dq[0](x) >= dq[1](x)) dq.pop_front();
        return dq[0](x);
    }
    ll query(ll x) { // min query, any x
        int lo = -1, hi = dq.size() - 1;
        while (lo + 1 < hi) {
            int mid = (lo + hi) / 2;
            if (dq[mid](x) >= dq[mid + 1](x)) lo = mid;
            else hi = mid;
        }
        return dq[hi](x);
    }
};

void solve() {
    int n; ll c; cin >> n >> c;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<ll> dp(n, LINF);
    dp[0] = 0;
    lichaotree st(1e6 + 1);
    // convexhull cht;
    for (int i = 1; i < n; i++) {
        // Naive O(n^2)
        // for (int j = 0; j < i; j++) {
        //     dp[i] = min(dp[i], dp[j] + (a[i] - a[j]) * (a[i] - a[j]) + c);
        // }
        
        // dp[i] = a[i] * a[i] + c + min{-2 * a[j] * a[i] + a[j] * a[j] + dp[j]}
        // Better O(nlogn)

        st.update({-2 * a[i - 1], a[i - 1] * a[i - 1] + dp[i - 1]});
        dp[i] = a[i] * a[i] + c + st.query(a[i]);
    
        // cht.add({- 2 * a[i - 1], a[i - 1] * a[i - 1] + dp[i - 1]});
        // dp[i] = a[i] * a[i] + c + cht.query(a[i]);
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