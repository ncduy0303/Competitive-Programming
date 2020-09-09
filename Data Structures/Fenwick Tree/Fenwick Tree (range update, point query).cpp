//MUST USE 1-INDEXED FOR FENWICK TREE

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

int ft[MAX_N] = {0}, arr[MAX_N], N, Q;

void adjust(int x, int v) {
    for(; x <= N; x += LSOne(x))
        ft[x] += v;
}

void range_adjust(int x, int y, int v) {
    adjust(x, v);
    adjust(y + 1, -v);
}

int sum(int x){
    int res = 0;
    for (; x; x -= LSOne(x))
        res += ft[x];
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    
    cin >> N >> Q;
    for(int i = 1; i <= N; i++) {
        cin >> arr[i];
        range_adjust(i, i, arr[i]);
    }
    
    while(Q--) {
        int t; cin >> t;
        if (t == 0) { //adjust
            int x, y, v; cin >> x >> y >> v;
            range_adjust(x, y, v);
        }
        else { //query
            int x; cin >> x;
            cout << sum(x) << "\n";
        }
    }
}
