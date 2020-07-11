/* NOI 2019: Pilot
Idea: Maintain the descending hull using stack
      The top element contains the value and position of the closet element to the left greater than the current element being processed
Time Complexity: O(N + Hi)
*/

#include <bits/stdc++.h>

using namespace std;

const int INF = 1 << 30;
const int MAX_N = 1000000 + 5;
const int MAX_L = 20; // ~ Log N
const long long MOD = 1e9 + 7;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) (S & (-S))
#define isBitSet(S, i) ((S >> i) & 1)

int N, Q;
long long ps[MAX_N];
stack<pair<int, int> > s;

void update(int val, int pos) {
	while (!s.empty() && s.top().first < val) {
		auto p = s.top(); s.pop();
		long long value = (pos - p.second) * (p.second - s.top().second);
		ps[p.first] += value;
	}
	s.push({val, pos});
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> N >> Q;
    s.push({MAX_N, -1}); //left extreme
    for (int i = 0; i < N; i++) {
        int val; cin >> val;
        update(val, i);
    }
    update(MAX_N, N); //right extreme

    for (int i = 1; i < MAX_N; i++)
        ps[i] += ps[i - 1];

    while (Q--) {
        int x; cin >> x;
        cout << ps[x] << "\n";
    }
}
