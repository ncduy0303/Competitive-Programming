// 2D Fenwick Tree
// Problem: https://cses.fi/problemset/task/1652/

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e4 + 5;

typedef long long ll;

#define LSOne(S) (S & (-S))

int N, M, Q, arr[MAX_N];
int ft[MAX_N][MAX_N];

void adjust(int x, int y, int v) {
    for (int tx = x; tx <= N; tx += LSOne(tx))
        for (int ty = y; ty <= N; ty += LSOne(ty))
            ft[tx][ty] += v;
}

int sum(int x, int y) {
    int res = 0;
    for (int tx = x; tx; tx -= LSOne(tx))
        for (int ty = y; ty; ty -= LSOne(ty))
            res += ft[tx][ty];
    return res;
}

int query(int x1, int y1, int x2, int y2) {
    return sum(x2, y2) - sum(x1 - 1, y2) - sum(x2, y1 - 1) + sum(x1 - 1, y1 - 1);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> N >> Q;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            char c; cin >> c;
            if (c == '*') adjust(i, j, 1);
        }
    }
    while (Q--) {
        int x1, x2, y1, y2; cin >> x1 >> y1 >> x2 >> y2;
        cout << query(x1, y1, x2, y2) << "\n";
    }
}
