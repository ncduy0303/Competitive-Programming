/* 
Given a string S (with length N) and a pattern P (with length M), find all the occurrence of P in S
Naive Approach: O(NM)
Z-algorithm Time complexity: O(N + M)
*/

#include <bits/stdc++.h>

using namespace std;

const int INF = 1 << 30;
const int MAX_N = 100000 + 5;
const int MAX_L = 20; // ~ Log N
const long long MOD = 1e9 + 7;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) (S & (-S))
#define isBitSet(S, i) ((S >> i) & 1)

void Z_Algo(string S, string P) {
    string T = P + "#" + S;
    int Z[T.size()], l = 0, r = 0; 
    Z[0] = T.size();
    
    for(int i = 0; i < T.size(); i++) {
        if(i > r) {
            l = r = i;
            while(r < T.size() && T[r] == T[r - l]) r++;
            Z[i] = r - l;
            r--;
        } else {
            int k = i - l;
            if (Z[k] < r - i + 1) Z[i] = Z[k];
            else {
                l = i;
                while (r < T.size() && T[r] == T[r - l]) r++;
                Z[i] = r - l; 
                r--;
            }
        }
        if(Z[i] == P.size()) 
            printf("P is found at index %d in S\n", i - P.size() - 1);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
  
    string S, P; cin >> S >> P;
    Z_Algo(S, P);
}
