// Basic geometry template for 2D Point (modified from kactl)
// All other extended functions from kactl should still work normally
// Problem link: https://cses.fi/problemset/task/2191/ (finding the area of a polygon)

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 5;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template <class T> struct Point {
    T x, y;
    Point() : x(0), y(0) {}
    Point(const T& x, const T& y) : x(x), y(y) {}

    friend std::ostream& operator<<(std::ostream& out, const Point& p) { return out << "(" << p.x << "," << p.y << ")"; }
    friend std::istream& operator>>(std::istream& in, Point& p) { return in >> p.x >> p.y; }

    friend bool operator==(const Point& a, const Point& b) { return tie(a.x, a.y) == tie(b.x, b.y); }
    friend bool operator!=(const Point& a, const Point& b) { return tie(a.x, a.y) != tie(b.x, b.y); }
    friend bool operator<(const Point& a, const Point& b) { return tie(a.x, a.y) < tie(b.x, b.y); }

    Point operator+(const Point& p) const { return Point(x + p.x, y + p.y); }
    Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
    Point operator*(const T& d) const { return Point(x * d, y * d); }
    Point operator/(const T& d) const { return Point(x / d, y / d); }

    T dot(const Point& p) const { return x * p.x + y * p.y; }
    T cross(const Point& p) const { return x * p.y - y  *p.x; }
    T cross(const Point& a, const Point& b) const { return (a - *this).cross(b - *this); }
    T dist2() const { return x * x + y * y; }
    double dist() const { return sqrt((double)dist2()); }
    double angle() const { return atan2(y, x); } // [-pi, pi] to x-axis

    Point unit() const { return *this / dist(); } // unit vector
    Point perp() const { return P(-y, x); } // rotates +90 degrees
    Point normal() const { return perp().unit(); }
    Point rotate(const double& a) const { return P(x*cos(a) - y*sin(a), x*sin(a) + y*cos(a)); } // ccw around (0,0)
};

using pt = Point<ll>;

template<class T> T polygonArea2(vector<Point<T>>& v) {
    T a = v.back().cross(v[0]);
    for (int i = 0; i < (int)v.size() - 1; i++) a += v[i].cross(v[i+1]);
    return a;
}

void solve() {
    int n; cin >> n;
    vector<pt> a(n);
    for (pt &p : a) cin >> p;
    cout << abs(polygonArea2(a)) << "\n";
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