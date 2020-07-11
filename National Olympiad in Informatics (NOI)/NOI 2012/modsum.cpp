/* NOI 2012 - Mod Sum
Simple solution: Apply recursion to calculate the total sum 
*/

#include <bits/stdc++.h>

using namespace std;

const int INF = 1 << 30;
const int MAX_N = 1000 + 5;
const int MAX_L = 20; // ~ Log N
const long long MOD = 1e9 + 7;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) (S & (-S))
#define isBitSet(S, i) ((S >> i) & 1)

int N;
long long ans = 0, v[MAX_N], w[MAX_N];

void compute(int idx, long long cur) {
    if(idx < N)
        for(long long i = v[idx]; i <= w[idx]; i++)
            compute(idx + 1, cur + i);
    else
        ans += ((cur*cur*cur*cur + 2*cur*cur) % 5) + 1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> N;
    for(int i = 0; i < N; i++)
        cin >> v[i] >> w[i];
    compute(0, 0);
    cout << ans;
}

