// Problem 1: A Whole New Word
// Idea: Brute Force (just generating all strings of given characters, return the first generated string that is not found in the dictionary)

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 5;
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

int N, L;
set<string> dict;
vector<set<char>> arr;

string build(string cur, int pos) {
    if (pos == L) {
        return (dict.find(cur) == dict.end()) ? cur : "-";
    }
    for (char c : arr[pos]) {
        string res = build(cur + c, pos + 1);
        if (res != "-") return res;
    }
    return "-";
}

void solve() {
    cin >> N >> L;
    dict.clear();
    arr.clear(); arr.resize(L);
    for (int i = 0; i < N; i++) {
        string str; cin >> str;
        dict.insert(str);
        for (int j = 0; j < L; j++) {
            arr[j].insert(str[j]);
        }
    }
    cout << build("", 0) << "\n";
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
