// Problem 3: Oversized Pancake Choppers

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

void solve() {
    int N, D; cin >> N >> D;
    ll arr[N];
    multiset<ll> ms;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
        ms.insert(arr[i]);
    }
    int ans = D; // Worst case requires D cuts
    for (int i = 0; i < N; i++) {
        for (int j = 1; j <= D; j++) {
            multiset<ll> removed;
            ll x = arr[i], y = j; // try x/y sized slices
            int rem = D; //remaining portions left to serve
            int ret = 0; //new upper bound on answer
            int mul = 1;
            for (mul = 1; mul <= rem; mul++) {
                if ((x * mul) / y * y == x * mul) {
                    long long sz = (x * mul) / y;
                    if (ms.count(sz)) {
                        ms.erase(ms.lower_bound(sz));
                        ret += mul - 1;
                        rem -= mul;
                        removed.insert(sz);
                        mul--;
                    }
                }
            }
            long long need = rem;
            long long minsz = (x+y-1)/y;
            for (auto it = ms.lower_bound(minsz); it != ms.end(); it++) {
                if (need <= 0) break;
                long long ele = *it;
                need -= (ele * y) / x;
            }
            if (need <= 0){
                ret += rem;
            }
            else ret += D + 42;
            ans = min(ans, ret);
            for (auto x: removed) ms.insert(x);
        }
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int tc; cin >> tc;
    for (int t = 1; t <= tc; t++) {
        cout << "Case #" << t  << ": ";
        solve();
    }
}
