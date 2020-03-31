// Cutting sticks problem
// Given a length L and N cutting points, find the minimum cost perform all N cuts
// The cost of a cut is equal to the length of the stick that we are cutting
// Example: UVa/10003 https://onlinejudge.org/external/100/10003.pdf
// Given n points(x, y) on a plane, find the closest distance between a pair of points

#include <bits/stdc++.h>

using namespace std;

const int INF = 1 << 30;
const int MAX_N = 100 + 5;
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
pair<ll, ll> pnts[MAX_N]; // <y, x> so that set automatically sorts based on y-coordinates
set<pair<ll, ll> > box;
double best = INF;

bool cmp(pair<ll, ll> a, pair<ll, ll> b){
    return (a.second < b.second);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    
}
