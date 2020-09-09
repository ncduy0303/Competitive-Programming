// Given N points (x, y) on a plane, find the minimum distance between a pair of points
// Problem link: UVa 10245 - The Closest Pair Problem

// Idea: Sweep Line Algorithm
// Reference: https://www.topcoder.com/community/competitive-programming/tutorials/line-sweep-algorithms/
// Time complexity: (NlogN)

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e4 + 5;
const double INF = 1e4;
const double EPS = 1e-9; // may need to use it to avoid floating point error when comparing double

struct pt {
    double x, y;
    bool operator < (pt a) { // sort based on x
        return (x == a.x) ? y < a.y : x < a.x;
    }
};

struct cmp { // custom comparator for set (sort based on y)
    bool operator() (pt a, pt b) {
        return (a.y == b.y) ? a.x < b.x : a.y < b.y;
    }
};

int N;
pt pnts[MAX_N];
set<pt, cmp> box;
double ans;

void solve() {
    for (int i = 0; i < N; i++)
        cin >> pnts[i].x >> pnts[i].y;
    sort(pnts, pnts + N); // sort bases on x-coordinates (from left to right)

    ans = INF;
    /* Naive approach O(N^2) -> Searching through all pair of points
    for (int l = 0; l < N; l++) {
        for (int r = l + 1; r < N; r++) {
            if (pnts[r].second - pnts[l].second > ans) break; // this helps speed up the approach
            ans = min(ans, hypot(pnts[r].first - pnts[l].first, pnts[r].second - pnts[l].second));
        }
    }*/
    box.clear();
    box.insert(pnts[0]);
    for (int l = 0, r = 1; r < N; r++) {
        // removing leftmost points that will not contribute to the minimum distance
        while (l < r && pnts[r].x - pnts[l].x >= ans)
            box.erase(pnts[l++]);

        auto lo = box.lower_bound({pnts[r].x, pnts[r].y - ans});
        auto hi = box.upper_bound({pnts[r].x, pnts[r].y + ans});
        for (; lo != hi; lo++)
            ans = min(ans, hypot(pnts[r].x - lo->x, pnts[r].y - lo->y));
        /* A more succinct way to write
        for (auto it = box.lower_bound({pnts[r].x - ans, pnts[r].y - ans}); it != box.end() && it->y - pnts[r].y <= ans; it++)
            ans = min(ans, hypot(pnts[r].x - it->x, pnts[r].y - it->y));
        */
        box.insert(pnts[r]);
    }

    if (ans == INF) cout << "INFINITY\n";
    else cout << fixed << setprecision(4) << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    while (cin >> N && N)
        solve();
}
