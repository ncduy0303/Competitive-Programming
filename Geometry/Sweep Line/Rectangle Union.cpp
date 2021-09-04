// Given n rectangles on a plane (they are all parallel to the axis), find the union area of all the rectangles
// Each rectangle is defined by two points (x1, y1) bottom left and (x2, y2) top right
// Time complexity: O(n^2), can be improved to O(nlogn)
// Problem link: https://cses.fi/problemset/task/1741/

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const l MOD = 1e9 + 7;
const ll INF = 1e9;

struct event {
    int id; // Index of rectangle in rects
    int type; // Type of event: 0 = Lower-left ; 1 = Upper-right
    event() {};
    event(int id, int type) : id(id), type(type) {};
};

struct point{
    int x, y;
};

int n, e = 0; // n = no. of rectangles, e = no. of events
point rects[MAX_N][2]; // Each rectangle consists of 2 points: [0] = lower-left ; [1] = upper-right
event events_v [2 * MAX_N]; // Events of horizontal sweep line
event events_h [2 * MAX_N]; // Events of vertical sweep line

bool in_set[MAX_N] = {0}; // Boolean array in place of balanced binary tree (set)
long long area = 0; // The output: Area of the union

bool compare_x(event a, event b) {
    return rects[a.id][a.type].x < rects[b.id][b.type].x;
}

bool compare_y(event a, event b) {
    return rects[a.id][a.type].y < rects[b.id][b.type].y;
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++){
        cin >> rects[i][0].x >> rects[i][0].y; // Lower-left coordinate
        cin >> rects[i][1].x >> rects[i][1].y; // Upper-right coordinate
        events_v[e] = event(i, 0);
        events_h[e++] = event(i, 0);
        events_v[e] = event(i, 1);
        events_h[e++] = event(i, 1);
    }
    sort(events_v, events_v + e, compare_x);
    sort(events_h, events_h + e, compare_y); // Pre-sort set of horizontal edges
    in_set[events_v[0].id] = 1;

    // Vertical sweep line
    for (int i = 1; i < e; i++){
        event cur = events_v[i], precur = events_v[i - 1];
        int cnt = 0; // Counter to indicate how many rectangles are currently overlapping

        // Delta_x: Distance between current sweep line and previous sweep line
        ll delta_x = rects[cur.id][cur.type].x - rects[precur.id][precur.type].x;
        if (delta_x < 0) continue;

        int begin_y;
        // Horizontal sweep line
        for (int j = 0; j < e; j++){
            if (in_set[events_h[j].id]){
                if (events_h[j].type == 0) {
                    if (cnt == 0) begin_y = rects[events_h[j].id][0].y; // Block starts
                    cnt++;
                }
                else {
                    cnt--;
                    if (cnt == 0) { // Block ends
                        ll delta_y = rects[events_h[j].id][1].y - begin_y;
                        area += delta_x * delta_y;
                    }
                }
            }
        }
        in_set[cur.id] = (cur.type == 0);
    }
    cout << area << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int tc; tc = 1;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t  << ": ";
        solve();
    }
}