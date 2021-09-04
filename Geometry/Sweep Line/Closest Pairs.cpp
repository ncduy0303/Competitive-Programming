// Given n points (x, y) on a plane, find the minimum distance between a pair of points
// Time complexity: (nlogn)
// Problem link: https://vjudge.net/problem/UVA-10245

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e4 + 1;
const ll MOD = 1e9 + 7;
const ll INF = 1e4;

struct pt {
    double x, y;
    bool operator< (pt a) { // sort based on x
        return (x == a.x) ? y < a.y : x < a.x;
    }
};

struct cmp { // custom comparator for set (sort based on y)
    bool operator() (pt a, pt b) {
        return (a.y == b.y) ? a.x < b.x : a.y < b.y;
    }
};

void solve() {
    while (true) {
        int n; cin >> n;
        if (!n) return;
        
        pt pnts[n];
        set<pt,cmp> box;
        for (int i = 0; i < n; i++) cin >> pnts[i].x >> pnts[i].y;
        sort(pnts, pnts + n); // sort bases on x-coordinates (from left to right)

        double ans = INF;
        /* Naive approach O(n^2) -> Searching through all pair of points
        for (int l = 0; l < n; l++) {
            for (int r = l + 1; r < n; r++) {
                if (pnts[r].second - pnts[l].second > ans) break; // this helps speed up the approach
                ans = min(ans, hypot(pnts[r].first - pnts[l].first, pnts[r].second - pnts[l].second));
            }
        }
        */
        box.clear();
        box.insert(pnts[0]);
        for (int l = 0, r = 1; r < n; r++) {
            // removing leftmost points that will not contribute to the minimum distance
            while (l < r && pnts[r].x - pnts[l].x >= ans)
                box.erase(pnts[l++]);
            auto lo = box.lower_bound({pnts[r].x, pnts[r].y - ans});
            auto hi = box.upper_bound({pnts[r].x, pnts[r].y + ans});
            for (; lo != hi; lo++)
                ans = min(ans, hypot(pnts[r].x - lo->x, pnts[r].y - lo->y));
            // A more succinct way to write
            // for (auto it = box.lower_bound({pnts[r].x - ans, pnts[r].y - ans}); it != box.end() && it->y - pnts[r].y <= ans; it++)
                // ans = min(ans, hypot(pnts[r].x - it->x, pnts[r].y - it->y));
            box.insert(pnts[r]);
        }

        if (ans == INF) cout << "INFINITY\n";
        else cout << fixed << setprecision(4) << ans << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int tc = 1;
    // cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t << ": ";
        solve();
    }
}