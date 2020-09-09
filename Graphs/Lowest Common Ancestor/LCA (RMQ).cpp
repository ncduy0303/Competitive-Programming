// We can convert the Lowest Common Ancestor (LCA) problem into the Range Minimum Query (RMQ) Problem
// This can then be solved using common methods such as segment tree or sparse table
// Details about the algorithm can be found here:
// https://www.topcoder.com/community/competitive-programming/tutorials/range-minimum-query-and-lowest-common-ancestor/

#include <bits/stdc++.h>

using namespace std;

const int INF = 1 << 30;
const int MAX_N = 100000 + 5;
const int MAX_L = 20; // ~ Log N
const long long MOD = 1e9 + 7;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) (S & (-S))
#define isBitSet(S, i) ((S >> i) & 1)

int N, Q, idx = 0;
int depth[MAX_N * 2], euler[MAX_N * 2], first[MAX_N];

int arr[MAX_N *  2], table[MAX_N * 2][MAX_L + 1], lg[MAX_N * 2 + 1];
int ST[4 * MAX_N];

bool visited[MAX_N] = {false};
vector<int> adj[MAX_N];

void dfs(int u, int h) {
    if(visited[u]) return;
    visited[u] = true;

    first[u] = idx;
    euler[idx] = u;
    depth[idx++] = h;

    for(int v : adj[u]) {
        if(!visited[v]) {
            dfs(v, h + 1);
            euler[idx] = u;
            depth[idx++] = h;
        }
    }
}

/* Segment Tree approach
void build(){
    for(int i = 2 * N - 1; i > 0; i--){
        ST[i] = min(ST[i * 2], ST[i * 2 + 1]);
    }
}

int RMQ(int l, int r){ //min query in [l..r)
    int ans = INF;
    for(l += N * 2, r += N * 2; l < r; l /= 2, r /= 2){
        if(l % 2 != 0) ans = min(ans, ST[l++]);
        if(r % 2 != 0) ans = min(ans, ST[--r]);
    }
    return ans;
}
*/

/* Sparse Table approach
void build_log_table() { // for O(1) range minimum query
    lg[1] = 0;
    for (int i = 2; i <= N; i++)
        lg[i] = lg[i/2] + 1;
}

void build_sparse_table() { // O(nlogn)
    for(int i = 0; i < N; i++)
        table[i][0] = arr[i];

    for(int j = 1; j <= MAX_L; j++) {
        for(int i = 0; i + (1 << j) <= N; i++)
            table[i][j] = min(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
    }
}

int RMQ(int l, int r){ // range minimum query in O(1)
    int j = lg[r - l + 1];
    return min(table[l][j], table[r - (1 << j) + 1][j]);
}
*/

int LCA(int u, int v) {
    int left = first[u], right = first[v];
    if (left > right) swap(left, right);
    return RMQ(left, right);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> N >> Q;
    for(int i = 0; i < N - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 0);

    /* Segment Tree approach
    for(int i = 0; i < N * 2; i++){ //all the elements in the array are assigned as leaves in the ST
        ST[i + N * 2] = depth[i];
    }
    build();
    */

    /* Sparse Table approach
    build_sparse_table();
    build_log_table();
    for(int i = 0; i < N * 2; i++){
        arr[i] = depth[i];
    }
    */

    while(Q--) {
        int u, v; cin >> u >> v;
        printf("LCA of %d and %d is %d\n", u, v, LCA(u, v));
    }
}
