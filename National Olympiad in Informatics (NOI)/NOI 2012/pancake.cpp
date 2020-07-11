/* NOI 2012 - Pancake
Applying BFS to to find the shortest path from the original configuration to the final one
Use DP table to avoid recalculating
*/

#include <bits/stdc++.h>

using namespace std;

const int INF = 1 << 30;
const int MAX_N = 1000 + 5;
const int MAX_L = 20; // ~ Log N
const long long MOD = 1e9 + 7;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) (S & (-S))
#define isBitSet(S, i) ((S >> i) & 1)

int TC, N;
int dp[9][9][9][9][9][9][9][9];
pair<int, int> arr[9];
vector<int> cur_arr(9, 0);

bool isSorted(vector<int> u) {
    bool sorted = true;
    for(int i = 1; i <= N; i++) {
        if(u[i] != arr[i].second) {
            sorted = false;
            break;
        }
    }
    return sorted;
}

bool cmp(pair<int, int> a, pair<int, int> b) {
    return a.first > b.first;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> TC;
    while(TC--) {
        cin >> N;
        for(int i = 1; i <= N; i++) {
            cin >> arr[i].first;
            cur_arr[i] = arr[i].second = i;
        }
        sort(arr + 1, arr + N + 1, cmp); //sort in decreasing order

        // Applying BFS + DP
        memset(dp, 0, sizeof dp);
        queue<pair<vector<int>, int> > Q;
        Q.push({cur_arr, 0});
        while(!Q.empty()) {
            vector<int> u = Q.front().first; int d = Q.front().second; Q.pop();
            if(isSorted(u)) {
                cout << d << "\n";
                break;
            }
            if(dp[u[0]][u[1]][u[2]][u[3]][u[4]][u[5]][u[6]][u[7]]) //visited
                continue;
            else {
                dp[u[0]][u[1]][u[2]][u[3]][u[4]][u[5]][u[6]][u[7]] = d;
                stack<int> S;
                for(int i = 1; i < N; i++) { //try flipping all possible positions and push them into the queue
                    vector<int> v(9, 0);
                    for(int j = 1; j < i; j++) //pushing in unchanged elements
                        v[j] = u[j];
                    for(int j = N; j >= i; j--) //reverse copying elements, pushing in the rightmost in first
                        v[N - j + i] = u[j];
                    if(!dp[v[0]][v[1]][v[2]][v[3]][v[4]][v[5]][v[6]][v[7]])  //only push if unvisited
                        Q.push({v, d + 1});
                }
            }
        }
    }
}
