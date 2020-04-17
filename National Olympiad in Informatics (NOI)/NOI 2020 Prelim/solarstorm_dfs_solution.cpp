/* NOI 2020 Prelim: Solar Storm
Idea: DFS
Time Complexity: O(N)
*/

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1000000 + 5;
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

// next_k[i] stores the rightmost module that can be protected if a shield is placed on module i
// next_k[next_k[i]] stores the rightmost module that can be protected by the same shield that is protecting module i
long long N, S, K, next_k[MAX_N], ans[MAX_N];
long long v[MAX_N], d[MAX_N];
vector<long long> children[MAX_N], ancestors;

void dfs(long long u) { // running dfs to find the rightmost proteced value at most S shields for each chosen module as the the left most protected
    if (ancestors.size() < S)
        ans[u] = N;
    else
        ans[u] = ancestors[ancestors.size() - S];

    ancestors.push_back(u);
    for (long long x : children[u])
        dfs(x);
    ancestors.pop_back();
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

    long long cur = 0;
    for(int i = 0; i < N; i++){
        while(d[cur + 1] - d[i] <= K) cur++;
        next_k[i] = cur;
    }

    for (int i = 0; i < N; i++)
        children[next_k[next_k[i]] + 1].push_back(i);

    for (long long x : children[N])
        dfs(x);

    long long best_index = 0;
    for(int i = 1; i < N; i++)
        if(v[ans[i]] - v[i] > v[ans[best_index]] - v[best_index]) // using prefix sum to quickly calculate the best position for the left most protected module
            best_index = i;

    long long cnt = 0, tmp = best_index;
    while(tmp < N && cnt < S) {
        tmp = next_k[next_k[tmp]];
        cnt++;
    }
    cout << cnt << "\n";

    best_index = next_k[best_index];
    cout << best_index + 1 << " ";
    while(--cnt > 0) {
        best_index = next_k[next_k[best_index] + 1];
        cout << best_index + 1 << " ";
    }
}
