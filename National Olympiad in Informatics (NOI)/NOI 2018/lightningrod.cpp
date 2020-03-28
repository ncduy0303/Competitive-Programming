/* NOI 2018: LightningRod
Idea: Maintain a stack of lightning rods
Time Complexity: O(N)
*/

#include <bits/stdc++.h>

using namespace std;

const int INF = 1 << 30;
const int MAX_N = 50000 + 5;
const int MAX_L = 20; // ~ Log N
const long long MOD = 1e9 + 7;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) (S & (-S))
#define isBitSet(S, i) ((S >> i) & 1)

// Fast OI template
inline int readInt() {
    int x=0; char ch=getchar_unlocked(); bool s=1;
    while(ch<'0'||ch>'9'){if(ch=='-')s=0;ch=getchar_unlocked();}
    while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar_unlocked();}
    return s?x:-x;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int N = readInt();
    stack<pair<int, int> > s;
    for(int i = 0; i < N; i++) {
        int x = readInt(), y = readInt();
        bool add = true;
        while(!s.empty()) {
            int tx = s.top().first, ty = s.top().second;
            if(x - tx <= ty - y) { // the new point is covered by the top point
                add = false;
                break;
            }
            else if(x - tx <= y - ty) s.pop(); // the new point covers the top point
            else break; // neither the top point or the new point covers each other
        }
        if(add) s.push({x, y});
    }
    cout << s.size();
}
