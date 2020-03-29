/* NOI 2020 Prelim: Visiting Singapore
Idea: Dynamic Programming
Time Complexity: O(NM)
*/

#include <bits/stdc++.h>

using namespace std;

const int INF = 1 << 30;
const int MAX_N = 1000000 + 5;
const int MAX_L = 20; // ~ Log N
const long long MOD = 1e9 + 7;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) (S & (-S))
#define isBitSet(S, i) ((S >> i) & 1)

// next_k[i] stores the rightmost module that can be protected if a shield is placed on module i
// next_k[next_k[i]] stores the rightmost module that can be protected by the same shield that is protecting module i
int N, S, K, next_k[MAX_N], ans[MAX_N];
pair<int, int> par[MAX_N];
long long v[MAX_N], d[MAX_N];

int dfs(int u, int depth) {
    if(depth == 0) return u;
    if(u == N) return N;

    int res = par[u].second ? dfs(par[u].first, depth - par[u].second) : dfs(next_k[next_k[u]] + 1, depth - 1);
    par[u] = {res, depth};
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> N >> S >> K;
    for(int i = 1; i < N; i++) {
        cin >> d[i];
        d[i] += d[i - 1];
    }
    d[N] = INF;
    for(int i = 1; i <= N; i++) {
        cin >> v[i];
        v[i] += v[i - 1];
    }

    int cur = 0;
    for(int i = 0; i < N; i++){
        while(d[cur + 1] - d[i] <= K) cur++;
        next_k[i] = cur;
    }

    for(int i = 0; i < N; i++)
        ans[i] = dfs(i, S);

    int best_index = 0;
    for(int i = 1; i < N; i++)
        if(v[ans[i]] - v[i] > v[ans[best_index]] - v[best_index])
            best_index = i;

    int cnt = 0, tmp = best_index;
    while(tmp < N && cnt < S) {
        tmp = next_k[next_k[tmp]];
        cnt++;
    }
    cout << cnt << "\n";

    best_index = next_k[best_index];
    cout << best_index + 1; cnt--;
    while(cnt > 0) {
        best_index = next_k[next_k[best_index] + 1];
        cout << " " << best_index + 1;
        cnt--;
    }
}
