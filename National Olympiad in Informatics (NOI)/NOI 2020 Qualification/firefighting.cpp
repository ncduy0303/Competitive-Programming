/* NOI 2020 Qualification: Firefighting
Idea: DFS
Time complexity: O(N)
*/

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 300000 + 5;
const int MAX_L = 20; // ~ Log N
const long long MOD = 1e9 + 7;
const long long INF = 1e18;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) (S & (-S))
#define isBitSet(S, i) ((S >> i) & 1)

int N;
ll K;
vi ans;
vii adj[MAX_N];

pair<ll, bool> dfs(int u, int par = 0, ll dist = INF) {
    ll max_overflow = -INF;
    ll max_underflow = 0;
    for (auto cur : adj[u]) {
        int v = cur.first, w = cur.second;
        if (v != par) {
            auto res = dfs(v, u, w);
            if (res.second)
                max_overflow = max(max_overflow, res.first);
            else
                max_underflow = max(max_underflow, res.first);
        }
    }
    pair<ll, bool> ret;
    if (max_overflow >= max_underflow)
        ret = {max_overflow - dist, true};
    else
        ret = {max_underflow + dist, false};

    if (!ret.second && ret.first > K) {
        ans.push_back(u);
        ret = {K - dist, true};
    }
    if (ret.second && ret.first < 0){
        ret = {0, false};
    }
    return ret;
}

void solve() {
    cin >> N >> K;
    for (int i = 0; i < N - 1; i++) {
        int x, y, w; cin >> x >> y >> w;
        adj[x].push_back({y, w});
        adj[y].push_back({x, w});
    }
    dfs(1);
    cout << ans.size() << "\n";
    for (int x : ans) cout << x << " ";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    solve();
}
