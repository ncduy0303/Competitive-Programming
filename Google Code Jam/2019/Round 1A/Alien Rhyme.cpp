// Problem 2: Alien Rhyme
// Idea: sort the reversed words alphabetically using a trie and take any two adjacent words with
// a longest common prefix, pair them, remove them from the list, and repeat

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e4 + 5;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;

#define LSOne(S) (S & (-S))
#define isBitSet(S, i) ((S >> i) & 1)

int N, num, ans;
int trie[MAX_N][26], cnt[MAX_N];

void insert(string s) { // insert a string into the trie
	int u = 0; // start at the root node
	for (char c : s) {
		if (!trie[u][c - 'A'])  // if this node has not been allocated
			trie[u][c - 'A'] = ++num; // then allocate the node and increase num by 1
		u = trie[u][c - 'A']; // move to the next node
	}
	cnt[u]++;
}

void solve() {
    ans = 0; num = 0;
    memset(trie, 0, sizeof trie);
    memset(cnt, 0, sizeof cnt);
    cin >> N;
    for (int i = 0; i < N; i++) {
        string s; cin >> s;
        reverse(s.begin(), s.end());
        insert(s);
    }
	for (int u = num; u > 0; u--) {
        for (int v = 0; v < 26; v++)
            if (trie[u][v])
                cnt[u] += cnt[trie[u][v]];
		if (cnt[u] >= 2) { // Greadily add them to the pair
			ans += 2;
			cnt[u] -= 2;
		}
	}
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
