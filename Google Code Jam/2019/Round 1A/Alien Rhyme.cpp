// Problem 3: Alien Rhyme
// Idea: Use a prefix tree

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 5;
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

const int ALPHA = 26;

void solve() {
    int n; cin >> n;
    vector<vector<int>> trie;
    trie.emplace_back(ALPHA, -1);
    vector<int> visited(1, 0), par(1, -1);
    while (n--) {
        string str; cin >> str;
        int cur = 0;
        for (int i = str.size() - 1; i >= 0; i--) {
            char c = str[i];
            int d = (int)(c - 'A');
            if (trie[cur][d] == -1) {
                trie[cur][d] = trie.size();
                trie.emplace_back(ALPHA, -1);
                visited.push_back(0);
                par.push_back(cur);
            }
            cur = trie[cur][d];
            visited[cur]++;
        }
    }
    int ans = 0;
    for (int i = trie.size() - 1; i >= 0; i--) {
        if (visited[i] < 2) continue;
        ans++;
        int u = i;
        while (u != -1) {
            visited[u] -= 2;
            u = par[u];
        }
    }
    cout << 2 * ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int tc; cin >> tc;
    for (int t = 1; t <= tc; t++) {
        cout << "Case #" << t  << ": ";
        solve();
    }
}
