// Kruskal Algorithm for finding Maximum Spanning Tree (MST)
// To use Kruskal, EdgeList representation for graph is preferred
// Time Complexity: O(ElogV)

#include <bits/stdc++.h>

const int MAX_N = 100000 + 5;

using namespace std;

int V, E, par[MAX_N], grpsize[MAX_N], num_grp = 0, mst_cost = 0;
vector< pair<int, pair<int, int> > > EdgeList;

int root(int x) {
    return (par[x] == x) ? x : par[x] = root(par[x]);
}

bool same(int x, int y) {
    return root(x) == root(y);
}

void unite(int x, int y) {
    x = root(x), y = root(y);
    num_grp -= same(x, y);
    if (grpsize[x] > grpsize[y]) {
        par[y] = x;
        grpsize[x] += grpsize[y];
    }
    else {
        par[x] = y;
        grpsize[y] += grpsize[x];
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> V >> E;
    // Initialize for UFDS
    for (int i = 0; i < V; ++i) par[i] = i, grpsize[i] = 1;
    num_grp = V;

    for (int i = 0; i < E; i++) {
        int u, v, w; cin >> u >> v >> w;
        EdgeList.push_back({w, {u, v}});
    }
    sort(EdgeList.begin(), EdgeList.end());

    for (int i = 0; i < E; i++) {
        auto edge = EdgeList[i];
        if (!same(edge.second.first, edge.second.second)) {
            mst_cost += edge.first;
            unite(edge.second.first, edge.second.second);
        }
    }

    cout << mst_cost;
}
