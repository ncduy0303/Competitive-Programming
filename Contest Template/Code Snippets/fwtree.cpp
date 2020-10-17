#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

// PUPQ & RUPQ & OST 
struct fwtree {
    const int MAX_L = 20;
    int n; vector<ll> ft;
    fwtree(int n): n(n), ft(n + 1) {}
    void update(int x, ll v) {
        for (; x <= n; x += x&-x)
            ft[x] += v;
    }
    void update(int l, int r, ll v) {
        update(l, v);
        update(r + 1, -v);
    }
    ll sum(int x) {
        ll res = 0;
        for (; x; x -= x&-x) 
            res += ft[x];
        return res;
    }
    ll query(int l, int r) {return sum(r) - sum(l - 1);}
    int find_by_order(int k) { // return 1 if k < 1 and returns N if k > N
        int sum = 0, pos = 0;
        for (int i = MAX_L; i >= 0; i--) {
            if (pos + (1 << i) < n && sum + ft[pos + (1 << i)] < k) {
                sum += ft[pos + (1 << i)];
                pos += (1 << i);
            }
        }
        return pos + 1; 
    }
    int order_of_key(int k) {return sum(k);}
};

// RURQ 
struct fwtree {
    int n; vector<ll> ft1, ft2;
    fwtree(int n): n(n), ft1(n + 1), ft2(n + 1) {}
    void update(vector<ll> &ft, int x, ll v) {
        for (; x <= n; x += x&-x) 
            ft[x] += v;
    }
    void update(int l, int r, ll v) {
        update(ft1, l, v);
        update(ft1, r + 1, -v);
        update(ft2, l, v * (l - 1));
        update(ft2, r + 1, -v * r);
    }
    ll sum(vector<ll> &ft, int x) {
        ll res = 0;
        for (; x; x -= x&-x) 
            res += ft[x];
        return res;
    }
    ll sum(int x) {return sum(ft1, x) * x - sum(ft2, x);}
    ll query(int l, int r) {return sum(r) - sum(l - 1);}
};

// PURQ 2D
struct fwtree {
    int n; vector<vector<ll>> ft;
    fwtree(int n): n(n), ft(n + 1, vector<ll>(n + 1)) {}
    void update(int x, int y, ll v) {
        for (int tx = x; tx <= n; tx += tx&-tx)
            for (int ty = y; ty <= n; ty += ty&-ty)
                ft[tx][ty] += v;
    }
    ll sum(int x, int y) {
        ll res = 0;
        for (int tx = x; tx; tx -= tx&-tx) 
            for (int ty = y; ty; ty -= ty&-ty)
                res += ft[tx][ty];
        return res;
    }
    ll query(int x1, int y1, int x2, int y2) {return sum(x2, y2) - sum(x1 - 1, y2) - sum(x2, y1 - 1) + sum(x1 - 1, y1 - 1);}
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
}