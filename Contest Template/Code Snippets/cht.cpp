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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
}