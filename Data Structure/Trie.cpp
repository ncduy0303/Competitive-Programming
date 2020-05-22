/* Trie (prefix tree) data structure
It is useful for string-related problems where we need to store strings based on their common prefix
Here we can implement it simply using a 2D array instead of pointers and linked lists
An example problem: https://codingcompetitions.withgoogle.com/kickstart/round/000000000019ffc7/00000000001d3ff3
*/

#include <bits/stdc++.h>

using namespace std;

// MAX_N here is used as the maximum number of nodes in the trie (aka total number of characters)
const int MAX_N = 2e6 + 5;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;

#define LSOne(S) (S & (-S))
#define isBitSet(S, i) ((S >> i) & 1)

int N, K, num, ans;
int trie[MAX_N][26], cnt[MAX_N];
// initially all numbers in trie are 0 (not allocated)
// cnt[u] = number of strings that end at node u in the trie => this is to mark the end of a string in the trie
// num stores the total number of allocated nodes in the trie

void dfs(int u = 0, int d = 0) {
    for (int v = 0; v < 26; v++) {
        if (trie[u][v]) {
            dfs(trie[u][v], d + 1);
            cnt[u] += cnt[trie[u][v]];
            // so now cnt[u] stores the total number of strings that has a common prefix from the root to node u
        }
    }
    while (cnt[u] >= K) { // greedily dividing into groups of K
        cnt[u] -= K;
        ans += d;
    }
}

void insert(string s) { // insert a string into the trie
	int u = 0; // start at the root node
	for (char c : s) {
		if (!trie[u][c - 'A'])  // if this node has not been allocated
			trie[u][c - 'A'] = ++num; // then allocate the node and increase num by 1
		u = trie[u][c - 'A']; // move to the next node
	}
	cnt[u]++;
}

bool search(string s) { // check if a string exist in the trie
	int u = 0;
	for (char c : s) {
        if (!trie[u][c - 'A']) return false;
        u = trie[u][c - 'A'];
	}
	return cnt[u] > 0;
}

void solve() {
    ans = 0; num = 0;
    memset(trie, 0, sizeof trie);
    memset(cnt, 0, sizeof cnt);
    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        string s; cin >> s;
        insert(s);
    }
    dfs();
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int tc; cin >> tc;
    for (int t = 1; t <= tc; t++) {
        cout << "Case #" << t  << ": ";
        solve();
    }
}
