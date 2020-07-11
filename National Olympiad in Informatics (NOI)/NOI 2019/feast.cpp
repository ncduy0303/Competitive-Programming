/* NOI 2019: Feast
Idea: Greedy (combine adjacent values with the same sign and remove negative values from the two ends)
Time Complexity: O(NlogN)
*/

#include <bits/stdc++.h>

using namespace std;

const int INF = 1 << 30;
const int MAX_N = 300000 + 5;
const int MAX_L = 20; // ~ Log N
const long long MOD = 1e9 + 7;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) (S & (-S))
#define isBitSet(S, i) ((S >> i) & 1)

struct block{
    int id, l, r;
	long long sum;
};

int N, K;
block b[MAX_N];
long long arr[MAX_N];
bool v[MAX_N];
priority_queue<pair<long long, int> > pq;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> N >> K;
    for(int i = 0; i < N; i++) cin >> arr[i];

    int j, idx = 0;
    for (int i = 0; i < N; i = j) {
		b[idx].sum = 0;
		b[idx].l = idx - 1;
		b[idx].r = idx + 1;

		for (j = i; j < N && (arr[i] * arr[j] >= 0); j++) // arr[i] and arr[j] must have the same sign
			b[idx].sum += arr[j];

		if (!(b[idx].sum < 0 && idx == 0)) idx++; // remove the first block if it is negative
	}

	if (idx != 0 && b[idx - 1].sum < 0) idx--; // remove the last block if it is negative
	if (idx == 0) { // if after remove, there's nothing left
		cout << 0;
		return 0;
	}

    b[0].l = b[idx - 1].r = -1; // extreme end points
	int remaining = idx / 2 + 1;
	for (int i = 0; i < idx; i++)
		pq.push({-abs(b[i].sum), i}); // negative of absolute value to have a min priority queue

    memset(v, 0, sizeof(v));
	while(remaining > K) {
		int i = pq.top().second; pq.pop();
		if(v[i]) continue;
		v[i] = true;
		remaining--;

		//merge it with left and right
		if (b[i].l == -1) { //extreme left
			v[b[i].r] = true;
			b[b[b[i].r].r].l = -1;
		}
		else if (b[i].r == -1) { //extreme right
			v[b[i].l] = true;
			b[b[b[i].l].l].r = -1;
		}
		else {
			v[b[i].r] = true;
			v[b[i].l] = true;

			b[i].sum += b[b[i].l].sum + b[b[i].r].sum;
			if (b[b[i].l].l != -1) {
				b[b[b[i].l].l].r = i;
			}
			b[i].l = b[b[i].l].l;
			if (b[b[i].r].r != -1) {
				b[b[b[i].r].r].l = i;
			}
			b[i].r = b[b[i].r].r;

			v[i] = 0;
			pq.push({-abs(b[i].sum), i});
		}
	}

	long long ans = 0;
	for(int i = 0; i < idx; i++)
		if (!v[i] && b[i].sum > 0)
			ans += b[i].sum;

	cout << ans;
}
