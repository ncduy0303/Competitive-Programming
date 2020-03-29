// Given an array of integers, find the maximum sum subarray

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

int N, arr[MAX_N], cur = 0, ans = 0;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
  
    cin >> N;
    for(int i = 0; i < N; i++) cin >> arr[i];
    
    cur = ans = arr[0];
    for(int i = 1; i < N; i++) {
        cur = max(0, cur);
        cur += arr[i];
        ans = max(ans, cur);
    }
    cout << ans;
}
