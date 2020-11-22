#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

// decreasing slope, increasing x, find maximum value
// modify accordingly for other cases
struct convexhull {
    struct line {
        ll m, c; // y = m * x + c
        line() {}
        line(ll m, ll c): m(m), c(c) {}
        ll operator()(ll x) {return m * x + c;}
        double intersect(line y) {return (double)(y.c - c) / (m - y.m);}
    };
    deque<line> dq;
    void add(line y) { // must be added in sorted order of slope
        while (dq.size() >= 2 && dq[dq.size() - 1].intersect(y) <= dq[dq.size() - 2].intersect(y)) dq.pop_back();
        dq.push_back(y);
    }
    ll query(ll x) { // must be used for sorted order of x
        while (dq.size() >= 2 && dq[0](x) <= dq[1](x)) dq.pop_front();
        return dq[0](x);
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    
}