// Find the largest rectangular area in a histogram 
// Use a monotonic stack {val, pos} to find the left border and right border at each position
// Time complexity: O(n)
// Problem link: https://www.spoj.com/problems/HISTOGRA/

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;



void solve() {
    while (true) {
        int n; cin >> n;
        if (!n) return;
        
        int arr[n], l[n], r[n];
        for (int i = 0; i < n; i++) cin >> arr[i];
        
        stack<int> st;
        // find left borders
        for (int i = 0; i < n; i++) {
            while (st.size() && arr[st.top()] >= arr[i]) st.pop();
            l[i] = st.size() ? st.top() + 1 : 0;
            st.push(i);
        }
        // clear stack
        while (st.size()) st.pop();
        // find right borders
        for (int i = n - 1; i >= 0; i--) {
            while (st.size() && arr[st.top()] >= arr[i]) st.pop();
            r[i] = st.size() ? st.top() - 1 : n - 1;
            st.push(i);
        }        
        
        ll mx = 0;
        for (int i = 0; i < n; i++) {
            ll cur = (ll) arr[i] * (r[i] - l[i] + 1);
            mx = max(mx, cur);
        }
        cout << mx << "\n";
    }
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