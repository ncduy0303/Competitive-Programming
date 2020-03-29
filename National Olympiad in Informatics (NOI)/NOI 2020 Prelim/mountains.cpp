/* NOI 2020 Prelim: Mountains
Idea: Try all possible value of y, using Fenwick Tree to count the number of smaller heights to the left and to the right of the current height
Trick: The absolute heights are not important, so convert them into relative heights
Time Complexity: O(NlogN)
*/

#include <bits/stdc++.h>

using namespace std;

const int INF = 1 << 30;
const int MAX_N = 300000 + 5;
const int MAX_L = 20; // ~ Log N
const long long MOD = 1e9 + 7;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) (S & (-S))
#define isBitSet(S, i) ((S >> i) & 1)

int N, height[MAX_N], ft[MAX_N], smallLeft[MAX_N], smallRight[MAX_N], ans = 0;
pair<int, int> arr[MAX_N];

void adjust(int x, int v) {
    for(; x <= N; x += LSOne(x))
        ft[x] += v;
}

int sum(int x) {
    int res = 0;
    for(; x; x -= LSOne(x))
        res += ft[x];
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> arr[i].first;
        arr[i].second = i;
    }
    sort(arr + 1, arr + N + 1);
    // convert from absolute height into relative height
    for(int i = 1; i <= N; i++) {
        if(i > 1 && arr[i].first == arr[i - 1].first)
            height[arr[i].second] = height[arr[i - 1].second];
        else
            height[arr[i].second] = i;
    }

    for(int i = 1; i <= N; i++) {
        smallLeft[i] = sum(height[i] - 1); // frequency of elements < height[i] to the left of i
        adjust(height[i], 1);
    }
    memset(ft, 0, sizeof ft);
    for(int i = N; i >= 1; i--) {
        smallRight[i] = sum(height[i] - 1); // frequency of elements < height[i] to the right of i
        adjust(height[i], 1);
    }
    for(int i = 1; i <= N; i++)
        ans += smallLeft[i] * smallRight[i];
    cout << ans;
}
