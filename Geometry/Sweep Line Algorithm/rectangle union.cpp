// Given N rectangles on a plane (they are all parallel to the axis), find the union area of all the rectangles
// Each rectangle is defined by two points (x1, y1) bottom left and (x2, y2) top right
// Problem link: https://cses.fi/problemset/task/1741/

// Idea: Sweep Line Algorithm (apply to 2 events simultaneously)
// At any instance, the set contains only the rectangles which intersect the sweep line
// Reference: https://www.topcoder.com/community/competitive-programming/tutorials/line-sweep-algorithms/
// Time complexity: O(N^2)
// It can be improved to O(NlogN) if we use a more efficient data structure (i.e segment tree)

#include <bits/stdc++.h>

using namespace std;

const int INF = 1 << 30;
const int MAX_N = 1e5 + 5;
const int MAX_L = 20; // ~ Log N
const long long MOD = 1e9 + 7;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) (S & (-S))
#define isBitSet(S, i) ((S >> i) & 1)

struct event {
    int id; // Index of rectangle in rects
    int type; // Type of event: 0 = Lower-left ; 1 = Upper-right
    event() {};
    event(int id, int type) : id(id), type(type) {};
};

struct point{
    int x, y;
};

int N, E = 0; // N = no. of rectangles, E = no. of events
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

int main() { /// x -> v; y -> h
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> N;
    for(int i = 0; i < N; i++){
        cin >> rects[i][0].x >> rects[i][0].y; // Lower-left coordinate
        cin >> rects[i][1].x >> rects[i][1].y; // Upper-right coordinate
        events_v[E] = event(i, 0);
        events_h[E++] = event(i, 0);
        events_v[E] = event(i, 1);
        events_h[E++] = event(i, 1);
    }
    sort(events_v, events_v + E, compare_x);
    sort(events_h, events_h + E, compare_y); // Pre-sort set of horizontal edges
    in_set[events_v[0].id] = 1;

    // Vertical sweep line
    for(int i = 1; i < E; i++){
        event cur = events_v[i], precur = events_v[i - 1];
        int cnt = 0; // Counter to indicate how many rectangles are currently overlapping

        // Delta_x: Distance between current sweep line and previous sweep line
        ll delta_x = rects[cur.id][cur.type].x - rects[precur.id][precur.type].x;
        if (delta_x < 0) continue;

        int begin_y;
        // Horizontal sweep line
        for (int j = 0; j < E; j++){
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

    cout << area;
}
