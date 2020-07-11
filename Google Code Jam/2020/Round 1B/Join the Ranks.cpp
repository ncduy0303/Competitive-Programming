// Problem 3: Join the Ranks
// Idea: Greedy + Constructive algorithm
// Min number of moves is always ceil((R * S - R)/2)

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1000000 + 5;
const int MAX_L = 20; // ~ Log N
const long long MOD = 1e9 + 7;
const long long INF = 1e18;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) (S & (-S))
#define isBitSet(S, i) ((S >> i) & 1)

vector<pair<int, int>> st;

void add(pair<int, int> t) {
    if (!st.empty() && st.back().first == t.first)
        st.back().second += t.second;
    else
        st.push_back(t);
}

void solve() {
    int R, S; cin >> R >> S;
    vector<pair<int, int>> ans;
    vector<pair<int, int>> arr;
    for (int i = 0; i < S; i++)
        for (int j = 1; j <= R; j++)
            arr.push_back({j, 1});

    while (arr.size() != R) {
        int p = 0;
        for (int i = 2; i < arr.size(); i++) {
            if (arr[0].first == arr[i].first) {
                p = i;
                break;
            }
        }
        if (p == arr.size() - 1) { // last card
            int sum = 0;
            for (int i = 1; i <= p; i++)
                sum += arr[i].second;
            ans.push_back({arr[0].second, sum});

            st.clear();
            for (int i = 1; i <= p; i++) add(arr[i]);
            add(arr[0]);
            arr = st;
            continue;
        }
        int sum = 0;
        for (int i = 2; i <= p; i++)
            sum += arr[i].second;
        ans.push_back({arr[0].second + arr[1].second, sum});

        st.clear();
        for (int i = 2; i <= p; i++) add(arr[i]);
        add(arr[0]); add(arr[1]);
        for (int i = p + 1; i < arr.size(); i++) add(arr[i]);
        arr = st;
    }

    if (arr[0].first != 1) {
        int sum = 0;
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i].first == 1) break;
            sum += arr[i].second;
        }
        ans.push_back({sum, R * S - sum});
    }

    cout << ans.size() << "\n";
    for (auto t : ans)
        cout << t.first << " " << t.second << "\n";
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
