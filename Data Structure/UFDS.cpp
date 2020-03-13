// Union-Find Disjoint Set
// Union by rank & Path compression

#include <bits/stdc++.h>

const int MAX_N = 100000 + 5;

using namespace std;

int N, par[MAX_N], grpsize[MAX_N], num_grp = 0;

int root(int x) {
    return (par[x] == x) ? x : par[x] = root(par[x]);
}

bool same(int x, int y) {
    return root(x) == root(y);
}

void unite(int x, int y) {
    x = root(x), y = root(y);
    num_grp -= same(x, y);
    if(grpsize[x] > grpsize[y]) {
        par[y] = x;
        grpsize[x] += grpsize[y];
    } else {
        par[x] = y;
        grpsize[y] += grpsize[x];
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    
    cin >> N;
    // Initialize
    for(int i = 0; i < N; ++i) par[i] = i, grpsize[i] = 1;
    num_grp = N;
}
