// Find the greatest common divisor (GCD) of two integers
// Time complexity: O(log(min(a, b)))
// Problem: https://dunjudge.me/analysis/problems/208/

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

// extended version to find x, y such that ax + by = gcd(a, b)
int gcd(int a, int b, int &x, int &y) {
    if (b == 0) {x = 1, y = 0; return a;}
    int x1, y1, d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

// find a solution of a Linear Diophantine Equation
bool find_any_solution(int a, int b, int c, int &x, int &y) {
    int d = gcd(abs(a), abs(b), x, y);
    if (c % d) return false; // no solution
    x *= c / d; 
    y *= c / d;
    if (a < 0) x = -x;
    if (b < 0) y = -y;
    return true;
}

void shift_solution(int a, int b, int &x, int &y, int cnt) {
    x += cnt * b;
    y -= cnt * a;
}

void solve() {
    int a, b; cin >> a >> b;
    cout << gcd(a, b) << "\n";

    // using C++ inbuilt function
    // cout << __gcd(a, b) << "\n";
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