// Given a stream of n input integers, maintain the median of the current array 
// Use a max heap to store the first half  (<= median) 
// Use a min heap to store the second half (> median)
// When a new number is inserted, compare it with the top of each heap and insert accordingly
// Time complexity: O(nlogn)
// Problem link: https://dunjudge.me/analysis/problems/338/

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

// The current median is stored as lo.top()

void solve() {
    int n; cin >> n;
    priority_queue<int> lo;
    priority_queue<int, vector<int>, greater<int>> hi;
    vector<int> ans;
    while (n--) {
        string s; cin >> s;
        if (s == "PUSH") {
            int x; cin >> x;
            if (hi.empty() || x <= hi.top()) // insert x to the lo heap if possible
                lo.push(x);
            else 
                hi.push(x);

            // the 2 heaps can become imbalanced, so need to fix it
            if (lo.size() > hi.size() + 1) {
                hi.push(lo.top());
                lo.pop();
            }
            if (lo.size() < hi.size()) {
                lo.push(hi.top());
                hi.pop();
            }
        }
        else { 
            // remove the current median
            lo.pop(); 
            // the 2 heaps can become imbalanced, so need to fix it
            if (lo.size() != hi.size()) {
                lo.push(hi.top());
                hi.pop();
            }
        }
    }

    // printing the final array in increasing order
    while (!lo.empty()) {
        ans.push_back(lo.top());
        lo.pop();
    }
    // need to reverse as we are popping from a max heap
    reverse(ans.begin(), ans.end()); 
    while (!hi.empty()) {
        ans.push_back(hi.top());
        hi.pop();
    }
    for (int x : ans)
        cout << x << " ";
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