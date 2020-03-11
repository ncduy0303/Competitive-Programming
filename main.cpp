#include <bits/stdc++.h>

using namespace std;

const int INF = 1 << 28;
const int MAX_N = 100 + 5;
const int MAX_L = 17;
const long long MOD = 1e9 + 7;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) (S & (-S))
#define isBitSet(S, i) ((S >> i) & 1)

int N;
string str[MAX_N];
int id[MAX_N];

int calc(){
    int res = 0;
    memset(id, 0, sizeof id);

    while(id[0] < str[0].length()) {
        char ch = str[0][id[0]];
        vector<int> cnt;
        for(int i = 0; i < N; i++) {
            int cur = 0;
            while(id[i] < str[i].size() && str[i][id[i]] == ch) {
                id[i]++; cur++;
            }
            if(cur == 0) return -1;
            cnt.push_back(cur);
        }

        sort(cnt.begin(), cnt.end());
        int med = cnt[N / 2];
        for(int i = 0; i < N; i++) {
            res += abs(cnt[i] - med);
        }

        for(int i = 0; i < N; i++) {
            if(id[i] != str[i].size()) return -1;
        }
        return res;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int TC; cin >> TC;
    for(int i = 1; i <= TC; i++) {
        cin >> N;
        for(int i = 0; i < N; i++) cin >> str[i];
        int ans = calc();

        cout << "Case #" << i << ": ";
        if(ans >= 0) cout << ans << "\n";
        else cout << "Fegla Won\n";
    }
}

