// Problem link: https://www.codechef.com/LRNDSA04/problems/ACM14KP1

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

struct pt {
    double x, y;
};

pt pts[MAX_N];

bool cmp_x(pt a, pt b) {return a.x < b.x;}
bool cmp_y(pt a, pt b) {return a.y < b.y;}
double dist(pt a, pt b) {return hypot(abs(a.x - b.x), abs(a.y - b.y));}
double perimeter(pt a, pt b, pt c) {return dist(a, b) + dist(b, c) + dist(c, a);}

double dac(int l, int r) {
    if (r - l <= 1) return INF;
    if (r - l == 2) return perimeter(pts[l], pts[l + 1], pts[l + 2]);

    int mid = (l + r) / 2;
    double d1 = dac(l, mid), d2 = dac(mid + 1, r);
    double ans = min(d1, d2);
    vector<pt> strip;
    for (int i = l; i <= r; i++) {
        if (abs(pts[i].x - pts[mid].x) < ans) strip.push_back(pts[i]);
    }
    sort(strip.begin(), strip.end(), cmp_y);
    for (int i = 0; i < strip.size(); i++) {
        for (int j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < ans; j++) {
            for (int k = j + 1; k < strip.size() && (strip[k].y - strip[j].y) < ans; k++) {
                ans = min(ans, perimeter(strip[i], strip[j], strip[k]));
            }
        }
    }
    return ans;
}

void solve() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) cin >> pts[i].x >> pts[i].y;
    sort(pts, pts + n, cmp_x);
    cout << fixed << setprecision(10) << dac(0, n - 1) << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int tc; cin >> tc;
    for (int t = 1; t <= tc; t++) {
        cout << "Case " << t  << ": ";
        solve();
    }
}