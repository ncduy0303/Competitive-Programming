// NOI 2020: Relay Marathon

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100000 + 5;
const int MAX_L = 20; // ~ Log N
const long long MOD = 1e9 + 7;
const int INF = 1e9;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) (S & (-S))
#define isBitSet(S, i) ((S >> i) & 1)

// dist[u] = shortest path to node u from any special nodes
// head[u] = closest special node w.r.t node u
// skip[u] = 1 means that this special node has already been marked during the first run (there are such 2 nodes)
int V, E, K, head[MAX_N];
vi d, dx1, dy1;
set<int> S;
bool skip[MAX_N];
vii adj[MAX_N];
vector<pair<ii, int>> EdgeList;
priority_queue<ii, vii, greater<ii> > Q;

void djikstra() {
    while (!Q.empty()) {
        int u = Q.top().second;
        Q.pop();
        for (auto cur : adj[u]) {
            int v = cur.first, w = cur.second;
            if (skip[v]) continue;
            if (d[u] + w < d[v]) {
                d[v] = d[u] + w;
                Q.push({d[v], v});
                head[v] = head[u];
            }
        }
    }
}

void run(int s) {
    while (!Q.empty()) Q.pop();
    d.assign(V + 1, INF);
    d[s] = 0;
    head[s] = s;
    Q.push({0, s});
    djikstra();
}

pair<ii, int> run_nearest() {
    while (!Q.empty()) Q.pop();
    d.assign(V + 1, INF);
    for (int s : S) {
        if (skip[s]) continue;
        d[s] = 0;
        Q.push({0, s});
        head[s] = s;
    }
    djikstra();
    int s1, e1, d1 = INF;
    for (auto e : EdgeList) {
        int u = e.first.first, v = e.first.second, w = e.second;
        if (skip[u] || skip[v])  continue;
        if (d[u] == INF || d[v] == INF || head[u] == head[v])  continue;
        if (d1 > d[u] + w + d[v]) {
            d1 = d[u] + w + d[v];
            s1 = head[u], e1 = head[v];
        }
    }
    return {{s1, e1}, d1};
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> V >> E >> K;
    while (E--) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
        EdgeList.push_back({{u, v}, w});
    }
    for (int i = 1; i <= K; i++) {
        int u; cin >> u;
        S.insert(u);
    }

    auto tmp = run_nearest();
    int x1 = tmp.first.first, y1 = tmp.first.second, d1 = tmp.second;

    // x1 and y1 are now the closet pair among all special nodes
    // There are 2 cases:
    // Case #1: x1 and y1 are actually x1 and x2 => Run 2 separate Dijkstra on x1 and x2 to find the best y1, y2 using an O(N) technique
    // Case #2: x1 and y1 are still x1 and y1 => Just create a new graph without x1, y1 and repeat the same process to find x2, y2
    // Final answer is the minimum between the two cases

    // Case #1
    run(x1); dx1 = d;
    run(y1); dy1 = d;
    int c1 = -1, c2 = -1;
    for (int c : S) {
        if (c == x1 or c == y1)  continue;
        if (c1 == -1 || dy1[c] <= dy1[c1]) {
            c2 = c1;
            c1 = c;
        } else if(c2 == -1 || dy1[c] < dy1[c2]) {
            c2 = c;
        }
    }
    int ans = INF, a1 = -1, a2 = -1, a3 = -1, a4 = -1;
    if (dx1[c1] != INF && dy1[c2] != INF) {
        ans = dx1[c1] + dy1[c2];
        a1 = x1, a2 = c1, a3 = y1, a4 = c2;
    }
    for (int x2 : S) {
        if (x2 == x1 || x2 == y1 || x2 == c1)  continue;
        if (dx1[x2] != INF && dy1[c1] != INF) {
            if (ans > dx1[x2] + dy1[c1]) {
                ans = dx1[x2] + dy1[c1];
                a1 = x1, a2 = x2, a3 = y1, a4 = c1;
            }
        }
    }

    // Case #2: removing s1 and e1 before repeating the same process
    skip[x1] = skip[y1] = 1;
    tmp = run_nearest();
    int d2 = tmp.second;
    if (d1 != INF and d2 != INF) {
        if (ans > d1 + d2) {
            ans = d1 + d2;
            a1 = x1, a2 = y1, a3 = tmp.first.first, a4 = tmp.first.second;
        }
    }

    cout << ans;
}
