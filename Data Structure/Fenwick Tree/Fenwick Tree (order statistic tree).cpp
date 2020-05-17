// Using a Fenwick Tree to implement an order statistic tree with the range of elements within a small range N
// Fenwick Tree can easily do a search(logN), an erase(logN), and an order_by_key(logN)
// The only new function that we need to implement is find_by_order(logN*logN)

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 5;
const int MAX_L = 20; // ~ Log N
const long long MOD = 1e9 + 7;
const long long INF = 1e9 + 7;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) (S & (-S))
#define isBitSet(S, i) ((S >> i) & 1)

int ft[MAX_N] = {0}, N, Q;

void adjust(int x, int v) {
    for (; x <= N; x += LSOne(x))
        ft[x] += v;
}

int sum(int x) {
    int res = 0;
    for (; x; x -= LSOne(x))
        res += ft[x];
    return res;
}

int find_by_order(int k) { // return the k-th smallest element using a basic binary search
    int lo = 1, hi = N + 1; // set upper bound as N + 1 so it will always return N + 1 if k > size of tree
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (k <= sum(mid))
            hi = mid;
        else
            lo = mid + 1;
    }
    return lo;
}

int order_by_key(int k) {
    return sum(k);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin >> N >> Q;
    for (int i = 0; i < N; i++) {
        int x; cin >> x;
        adjust(x, 1); // insert(x)
    }
    adjust(x, 1); // insert(x);
    adjust(x, -1); // delete(x)
    find_by_order(k); // return k-th smallest element
    order_by_key(x); // return the rank of x <=> number of elements smaller than x plus one
}
