#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 5;
const int MAX_M = 2e6 + 5;
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

int n, k, c[MAX_M][26], cnt[MAX_M], timer = 0;
ll ans;

void dfs(int u = 0, int d = 0) {
    for (int v = 0; v < 26; v++) {
        if (c[u][v]) {
            dfs(c[u][v], d + 1);
            cnt[u] += cnt[c[u][v]];
        }
    }
    while (cnt[u] >= k) {
        cnt[u] -= k;
        ans += d;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        int u = 0;
        for (char d : s) {
            if (!c[u][d - 'A']) {
                c[u][d - 'A'] = ++timer;
            }
            u = c[u][d - 'A'];
        }
        cnt[u]++;
    }
    dfs();
    cout << ans;
}
