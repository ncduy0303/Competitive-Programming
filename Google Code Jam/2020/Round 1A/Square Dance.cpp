/*
Idea: This one is just a heavy simulation & implementation problem, use C++ STL Set to store eliminated candidates to speed up
*/

#include <bits/stdc++.h>

using namespace std;

set<pair<int, int> > tr;

struct cell {
    int l, r, u, d, val;
};

vector<vector<cell> > arr;

//check if (i, j) should be eliminated
bool check(int i, int j) {
	int num = 0, sum = 0;
	if (arr[i][j].l != -1) {
		num++;
		sum += arr[i][arr[i][j].l].val;
	}
	if (arr[i][j].r != -1) {
		num++;
		sum += arr[i][arr[i][j].r].val;
	}
	if (arr[i][j].u != -1) {
		num++;
		sum += arr[arr[i][j].u][j].val;
	}
	if (arr[i][j].d != -1) {
		num++;
		sum += arr[arr[i][j].d][j].val;
	}
	return arr[i][j].val * num < sum;
}

// add/remove (i, j)
void check2(int i, int j) {
	if (check(i, j)) tr.insert({i, j});
	else tr.erase({i, j});
}

void solve() {
    int R, C; cin >> R >> C;
    arr = vector<vector<cell> >(R, vector<cell>(C));
    long long sum = 0;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            cin >> arr[i][j].val;
    // compass neighbors & sum of all elements
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            sum += arr[i][j].val;
            arr[i][j].l = j - 1;
            arr[i][j].u = i - 1;
            arr[i][j].r = (j + 1 < C) ? j + 1 : -1;
            arr[i][j].d = (i + 1 < R) ? i + 1 : -1;
        }
    }
    // 1st elimination
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            check2(i, j);

    // entire simulation
    long long ans = 0;
    bool change = true;
    while (change) {
        change = false;
        ans += sum;
        // remove competitors and update their neighbors
		set<pair<int, int> > tr2 = tr;
		tr.clear();
        for(auto x : tr2) {
            change = true;
            int i = x.first, j = x.second;
			sum -= arr[i][j].val; // remove (i, j)
			// update neighbors
            if (arr[i][j].l != -1) {
                arr[i][arr[i][j].l].r = arr[i][j].r;
                check2(i, arr[i][j].l);
            }
            if (arr[i][j].r != -1) {
                arr[i][arr[i][j].r].l = arr[i][j].l;
                check2(i, arr[i][j].r);
            }
            if (arr[i][j].u != -1) {
                arr[arr[i][j].u][j].d = arr[i][j].d;
                check2(arr[i][j].u, j);
            }
            if (arr[i][j].d != -1) {
                arr[arr[i][j].d][j].u = arr[i][j].u;
                check2(arr[i][j].d, j);
            }
            tr.erase({i, j});
        }
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int TC; cin >> TC;
    for (int t = 1; t <= TC; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
}
