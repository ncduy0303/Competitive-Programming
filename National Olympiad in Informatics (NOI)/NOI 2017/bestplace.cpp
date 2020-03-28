/* NOI 2017 - Best Place
Idea: Sorting (the required point is the median point for both the x-coordinates and y-coordinates
Time Complexity: O(NlogN)
*/

#include <bits/stdc++.h>

using namespace std;

const int INF = 1 << 30;
const int MAX_N = 100000 + 5;
const int MAX_L = 20; // ~ Log N
const long long MOD = 1e9 + 7;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) (S & (-S))
#define isBitSet(S, i) ((S >> i) & 1)

int N, x[MAX_N], y[MAX_N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> N;
    for(int i = 0; i < N; i++)
        cin >> x[i] >> y[i];

    sort(x, x + N); sort(y, y + N);

    cout << x[N / 2] << " " << y[N / 2];
}

