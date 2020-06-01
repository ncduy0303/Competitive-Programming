// Running Median (Median Heap)
// Problem: given a stream of input integers (N), we need to maintain the median of the current array in the most efficient way
// Idea: use a max heap to store the first half of current integers (<= median) and a min heap to store the second half (> median)
// As we insert s new number, just need to compare it with the top of each heap and insert accordingly => Time complexity: O(NlogN)
// We can also remove the current median if we want to
// Here if the number of elements is odd, median will be the element to the left of the middle

// Naive approach: sort the entire array every time we try to insert a new number => time complexity: O(N^2logN)
// Another way to do this problem is to use an ordered set tree, but the constant factor is very large & we don't need to maintain the sorted order of the array

// Problem link: https://dunjudge.me/analysis/problems/338/

#include <bits/stdc++.h>

using namespace std;

int n, median;
priority_queue<int> lo;
priority_queue<int, vector<int>, greater<int>> hi;
vector<int> ans;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> n;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        if (s == "PUSH") {
            int x; cin >> x;
            if (lo.empty() && hi.empty()) {
                lo.push(x);
                median = x;
            }
            else if (lo.size() > hi.size()) {
                if (x < median) {
                    hi.push(lo.top());
                    lo.pop(); lo.push(x);
                }
                else hi.push(x);
                median = lo.top();
            }
            else if (lo.size() < hi.size()) {
                if (x > median) {
                    lo.push(hi.top());
                    hi.pop(); hi.push(x);
                }
                else lo.push(x);
                median = lo.top();
            }
            else { // lo.size() == hi.size()
                if (x < median) {
                    lo.push(x);
                    median = lo.top();
                }
                else {
                    hi.push(x);
                    median = hi.top();
                }
            }
        }
        else { // POP (remove the median)
            if (lo.size() < hi.size()) {
                hi.pop();
                if (!lo.empty()) median = min(lo.top(), hi.top());
            }
            else if (lo.size() > hi.size()) {
                lo.pop();
                if (!hi.empty()) median = min(lo.top(), hi.top());
            }
            else { // lo.size() == hi.size()
                if (lo.top() == median) {
                    lo.pop();
                    median = hi.top();
                }
                else {
                    hi.pop();
                    median = lo.top();
                }
            }
        }
    }

    // printing the final array in increasing order
    while (!lo.empty()) {
        ans.push_back(lo.top());
        lo.pop();
    }
    reverse(ans.begin(), ans.end()); // need to reverse as we are popping from a max heap
    while (!hi.empty()) {
        ans.push_back(hi.top());
        hi.pop();
    }
    for (int x : ans)
        cout << x << " ";
}

