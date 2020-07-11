// Idea: if x and y have the same parity, impossible
// If x is odd we branch to reduced problems for ((x+1)/2, y/2) and ((x-1)/2, y/2), similarly for the case when y is odd
// => method is deterministic: we always have only one choice out of the four possible directions

#include <bits/stdc++.h>

using namespace std;

int mod (int x, int m) {
    int res = x % m;
    if (res < 0) res += m;
    return res;
}

string dfs(int x, int y, int d) {
    if (d > 40) return "#"; // running out of bound
    if (x == 0 && y == 0) return "";
    if (mod(x, 2) == mod(y, 2)) return "#";

    string res = "#", cur;
    if (mod(x, 2) == 1) {
        cur = dfs((x + 1) / 2, y / 2, d + 1);
        if (res == "#" || res.size() > cur.size())
            if (cur != "#") res = "W" + cur;
        cur = dfs((x - 1) / 2, y / 2, d + 1);
        if (res == "#" || res.size() > cur.size())
            if (cur != "#") res = "E" + cur;
    }
    else {
        cur = dfs(x / 2, (y + 1) / 2, d + 1);
        if (res == "#" || res.size() > cur.size())
            if (cur != "#") res = "S" + cur;
        cur = dfs(x / 2, (y - 1) / 2, d + 1);
        if (res == "#" || res.size() > cur.size())
            if (cur != "#") res = "N" + cur;
    }
    return res;
}

void solve() {
    int x, y; cin >> x >> y;
    string ans = dfs(x, y, 0);
    if (ans == "#") cout << "IMPOSSIBLE\n";
    else cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int tc; cin >> tc;
    for (int t = 1; t <= tc; t++) {
        cout << "Case #" << t  << ": ";
        solve();
    }
}
