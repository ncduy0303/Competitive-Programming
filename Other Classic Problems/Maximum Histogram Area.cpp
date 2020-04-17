// Problem: Find the largest rectangular area possible in a given histogram 
// where the largest rectangle can be made of a number of contiguous bars

// Idea: Maintain an ascending stack of height, whenever we process a new height, popping out all higher heights at the top of the stack
//       and update the maximum area 
// Remember to add a 0 height at the end to process everthing before it (greater height than 0)

// Reference: https://www.geeksforgeeks.org/largest-rectangle-under-histogram/

#include <bits/stdc++.h>

using namespace std;

const long long INF = 1e18;
const int MAX_N = 200000 + 5;
const int MAX_L = 20; // ~ Log N
const long long MOD = 1e9 + 7;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) (S & (-S))
#define isBitSet(S, i) ((S >> i) & 1)

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int n; cin >> n;
    int arr[n + 1] = {0}; 
    for (int i = 0; i < n; i++) cin >> arr[i];
    stack<int> s;
    int max_area = 0;
    for (int i = 0; i <= n; i++) {
        while (!s.empty() && arr[s.top()] > arr[i]) {
            int h = arr[s.top()];
            s.pop();
            int cur_area = h * (s.empty() ? i : i - s.top() - 1);
            max_area = max(max_area, cur_area);
        }
        s.push(i);
    }
    cout << max_area;
}
