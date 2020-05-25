// Given N points (x, y) on a plane, find the minimum distance between a pair of points
// Idea: Sweep Line Algorithm
// Reference: https://www.topcoder.com/community/competitive-programming/tutorials/line-sweep-algorithms/
// Time complexity: (NlogN)

#include <bits/stdc++.h>

using namespace std;

const int INF = 1 << 30;
const int MAX_N = 10000 + 5;
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

    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> pnts[i].second >> pnts[i].first;
    sort(pnts, pnts + N, cmp); // sort bases on x-coordinates (from left to right)

    box.insert(pnts[0]);
    int left = 0;
    for (int i = 1; i < N; i++){
        while (left < i && pnts[left].second - pnts[i].second > best)
            box.erase(pnts[left++]);
        for (auto it = box.lower_bound({pnts[i].second - best, pnts[i].first - best}); it != box.end() && it->first - pnts[i].first <= best; it++)
            best = min(best, hypot(pnts[i].first - it->first, pnts[i].second - it->second));
        box.insert(pnts[i]);
    }
    cout << best;
}
