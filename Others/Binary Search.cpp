#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 5;
const int MAX_L = 20; // ~ Log N
const long long MOD = 1e9 + 7;
const long long INF = 1e9 + 7;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) (S & (-S))
#define isBitSet(S, i) ((S >> i) & 1)

bool valid(int mid) {
    // do something to check whether mid satisfies the problem
    return true;
}

void solve() {
    int lo = 0, hi = INF;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (valid(mid)) hi = mid;
        else lo = mid + 1;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    solve();
}
