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