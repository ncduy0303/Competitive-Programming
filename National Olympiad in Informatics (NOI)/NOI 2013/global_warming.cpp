/* NOI 2013 - Global Warming
Idea: Keeping track of all the peaks and troughs, slowly decreasing sea level from top while counting the number of islands
      Be careful when handling special cases (peaks & troughs at the same height)
Time Complexity: O(nlogn)
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

int N, arr[MAX_N];
vector<int> peaks, troughs;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> N;
    for(int i = 1; i <= N; i++) cin >> arr[i];
    arr[0] = arr[1];

    int prvNum = arr[0], prvPrvNum = arr[0], plateau = 0; //0: NA, 1: peak, 2: valley
    for(int i = 0; i <= N; i++) {
        int tmp = arr[i];
        if(tmp < prvNum && prvPrvNum < prvNum)        peaks.push_back(prvNum);
        else if(tmp > prvNum && prvPrvNum > prvNum)   troughs.push_back(prvNum);
        else if(tmp == prvNum && prvPrvNum < prvNum)  plateau = 1;
		else if(tmp == prvNum && prvPrvNum > prvNum)  plateau = 2;
		else if(plateau != 0){
			if(plateau == 1){
				if(tmp < prvNum){ //plateau complete
					peaks.push_back(prvNum);
					plateau = 0;
				}
				else if(tmp > prvNum){ //plateau failed
					plateau = 0;
				}
			}
			else if(plateau == 2){
				if(tmp > prvNum){ //plateau complete
					troughs.push_back(prvNum);
					plateau = 0;
				}
				else if(tmp < prvNum){ //plateau failed
					plateau = 0;
				}
			}
		}
		prvPrvNum = prvNum;
		prvNum = tmp;
    }

    if(arr[1] > arr[2])     peaks.push_back(arr[0]);
	if(arr[N] > arr[N - 1]) peaks.push_back(arr[N]);
	sort(peaks.begin(), peaks.end(), greater<int>());
	sort(troughs.begin(), troughs.end(), greater<int>());
	int ans = 0, cur = 0;
	for(int i = 0, j = 0; i < peaks.size(); i++){
		cur++;
		while(troughs[j] >= peaks[i]){
			j++;
			cur--;
		}
		ans = max(ans, cur);
	}
	if(ans == 0 && arr[0] == arr[N]) ans++;
	cout << ans;
}
