// Problem 2: Bit Party
// Idea: Binary search the minimal finishing time
// To check whether it is possible for that chosen time, greedily assign R robots to the most efficient cashiers

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1000 + 5;

typedef long long ll;

ll R, B, C;

struct cashier{
    ll M, S, P;
} arr[MAX_N];

bool valid(ll mid) {
    vector<ll> capacity;
    for (int i = 0; i < C; i++) {
        ll cur = max(0ll, min((mid - arr[i].P) / arr[i].S, arr[i].M));
        capacity.push_back(cur);
    }
    sort(capacity.rbegin(), capacity.rend());
    ll sum = 0;
    for (int i = 0; i < R; i++) sum += capacity[i];
    return sum >= B;
}

void solve() {
    cin >> R >> B >> C;
    ll lo = 0, hi = 0;
    for (int i = 0; i < C; i++) {
        cin >> arr[i].M >> arr[i].S >> arr[i].P;
        hi = max(hi, arr[i].M * arr[i].S + arr[i].P);
    }
    while (lo < hi) {
        ll mid = (lo + hi) / 2;
        if (valid(mid)) hi = mid;
        else lo = mid + 1;
    }
    cout << lo << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int tc; cin >> tc;
    for (int t = 1; t <= tc; t++) {
        cout << "Case #" << t  << ": ";
        solve();
    }
}
