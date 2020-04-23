// Idea: First of all, find one point inside the circle
// Then use binary search in 4 directions to find the edge points of the circle
// Mid-point of the 2 horizontal edge points give the x-coordinate of the center of the circle
// Similar for the y-coordinate
#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

void solve() {
    int cx = 0, cy = 0;
    int check[4] = {-3 * INF / 4, -INF / 4, INF / 4, 3 * INF / 4};
    // Finding 1 point inside the circle first (only need 16 tries because at least one of them must be inside the circle)
    for (int x : check) {
        for (int y : check) {
            cout << x << " " << y << endl;
            string res; cin >> res;
            if (res == "CENTER") return;
            if (res == "HIT") cx = x, cy = y;
        }
    }

    int min_x, min_y, max_x, max_y, lo, hi;

    // Finding min_x
    lo = -INF, hi = cx;
    while (hi - lo > 1) {
        int mid = (lo + hi) / 2;
        cout << mid << " " << cy << endl;
        string res; cin >> res;
        if (res == "CENTER") return;
        if (res == "HIT") hi = mid;
        else lo = mid;
    }
    min_x = hi;

    // Finding max_x
    lo = cx, hi = INF;
    while (hi - lo > 1) {
        int mid = (lo + hi) / 2;
        cout << mid << " " << cy << endl;
        string res; cin >> res;
        if (res == "CENTER") return;
        if (res == "HIT") lo = mid;
        else hi = mid;
    }
    max_x = lo;

    // Finding min_y
    lo = -INF, hi = cy;
    while (hi - lo > 1) {
        int mid = (lo + hi) / 2;
        cout << cx << " " << mid << endl;
        string res; cin >> res;
        if (res == "CENTER") return;
        if (res == "HIT") hi = mid;
        else lo = mid;
    }
    min_y = hi;

    // Finding max_y
    lo = cy, hi = INF;
    while (hi - lo > 1) {
        int mid = (lo + hi) / 2;
        cout << cx << " " << mid << endl;
        string res; cin >> res;
        if (res == "CENTER") return;
        if (res == "HIT") lo = mid;
        else hi = mid;
    }
    max_y = lo;

     // Taking the final answer as the midpoints
    cx = (min_x + max_x) / 2;
    cy = (min_y + max_y) / 2;
    cout << cx << " " << cy << endl;
    string res; cin >> res;
    assert(res == "CENTER");
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int tc, a, b; cin >> tc >> a >> b;
    for (int t = 1; t <= tc; t++) {
        //cout << "Case #" << t  << ": ";
        solve();
    }
}
