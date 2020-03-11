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

int ft[MAX_N] = {0}, arr[MAX_N] N, Q;

void adjust(int x, int v) {
    for(; x <= N; x += LSOne(x))
        ft[x] += v;
}

int sum(int x){
    int res = 0;
    for (; x; x -= LSOne(x))
        res += ft[x];
    return res;
}

int rsq(int x, int y) { //range sum query, inclusive
    return sum(y) - (x == 1 ? 0 : sum(x - 1));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    
    cin >> N >> Q;
    for(int i = 1; i <= N; i++) {
        cin >> arr[i];
        adjust(i, arr[i]);
    }
    
    while(Q--) {
        int t; cin >> t;
        if (t == 0) { //query
            int x, y; cin >> x >> y;
            cout << rsq(x, y) << "\n";
        }
        else { //adjust
            int x, v; cin >> x >> v;
            adjust(x, v);
        }
    }
}
