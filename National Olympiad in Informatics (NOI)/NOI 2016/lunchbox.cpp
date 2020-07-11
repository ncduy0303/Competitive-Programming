/* NOI 2016 - Lunchbox
Idea: Sorting + Greedy (just distribute to the school that requested the smalles boxes first)
Time Complexity: O(mlogm)
*/

#include <bits/stdc++.h>

using namespace std;

const int INF = 1 << 30;
const int MAX_N = 60000 + 5;
const int MAX_L = 20; // ~ Log N
const long long MOD = 1e9 + 7;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) (S & (-S))
#define isBitSet(S, i) ((S >> i) & 1)

int N, m, arr[MAX_N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> N >> m;
    for(int i = 0; i < m; i++) cin >> arr[i];
    sort(arr, arr + m);

    int sum = 0, cnt = 0;
    for(int i = 0; i < m; i++) {
        if(sum + arr[i] <= N) {
            sum += arr[i];
            cnt++;
        }
        else break;
    }
    cout << cnt;
}

