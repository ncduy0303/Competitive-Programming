// Mo's Algorithm for answering offline queries
// Time complexity: O(N*sqrt(N))
// Application in D-query problem (https://www.spoj.com/problems/DQUERY/)
// For each query (l, r), count the number of distinct numbers in the range [l, r]

#include <bits/stdc++.h>

using namespace std;

const int INF = 1 << 30;
const int MAX_N = 100000 + 5;
const int BLOCK = sqrt((double)MAX_N);
const int MAX_L = 20; // ~ Log N
const long long MOD = 1e9 + 7;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) (S & (-S))
#define isBitSet(S, i) ((S >> i) & 1)

struct node{
    int l, r, id;
} query[MAX_N];

int N, Q, arr[MAX_N], ans[MAX_N], cnt[1000005] = {0}, cur = 0;

bool cmp(node a, node b){
    if(a.l/BLOCK != b.l/BLOCK)
        return a.l/BLOCK < b.l/BLOCK;
    else
        return a.r < b.r;
        
        //trick to reduce run time by 1/2
        //return (a.r < b.r) ^ ((a.l/BLOCK) % 2);
}

void add(int pos){
    cnt[arr[pos]]++;
    if(cnt[arr[pos]] == 1) cur++;
}

void subtract(int pos){
    cnt[arr[pos]]--;
    if(cnt[arr[pos]] == 0) cur--;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    
    cin >> N >> Q;
    for(int i = 0; i < N; i++) 
        cin >> arr[i];
    for(int i = 0; i < Q; i++) {
        cin >> query[i].l >> query[i].r; 
        query[i].id = i;
    }
    sort(query, query + Q, cmp);
    
    int curL = 0, curR = 0;
    for(int i = 0; i < Q; i++) {
        int L = query[i].l, R = query[i].r;
        while(curL < L) {
            subtract(curL);
            curL++;
        }
        while(curL > L) {
            add(curL - 1);
            curL--;
        }
        while(curR <= R) {
            add(curR);
            curR++;
        }
        while(curR > R + 1) {
            subtract(curR - 1);
            curR--;
        }
        ans[query[i].id] = cur;
    }
    
    for(int i = 0; i < Q; i++)
        cout << ans[i] << "\n";
}
