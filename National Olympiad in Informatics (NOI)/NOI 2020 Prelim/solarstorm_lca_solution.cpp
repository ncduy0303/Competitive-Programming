#include <bits/stdc++.h>
using namespace std;

const int LOGN = 21, N = 1e6 + 5;
#define ll long long

ll A[N], prefix[N];
int V[N];
int nxt[N], before[N], parent[LOGN][N];

int n, s, ans_start;
ll ans = 0;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int diff;
  ll k;
  cin>>n>>s>>k;
  A[0] = 0;
  for(int i = 1; i < n; i++) {
    cin>>diff;
    A[i] = A[i - 1] + diff;
  }
  for(int i = 0; i < n; i++) {
    cin>>V[i];
    prefix[i] = (i == 0 ? 0 : prefix[i - 1]) + V[i];
  }
  prefix[n] = prefix[n - 1];
  A[n] = A[n - 1] + 2*k;
  int current_ptr = 0;
  nxt[n] = n;
  for(int i = 0; i < n; i++) {
    for(int j = current_ptr; j <= n; j++) {
      if(A[j] - A[i] > k) {
        current_ptr = j;
        nxt[i] = j;
        break;
      }
    }
  }
  current_ptr = n;
  for(int i = n; i >= 0; i--) {
    for(int j = current_ptr; j >= -1; j--) {
      if(j == -1 or A[i] - A[j] > k) {
        current_ptr = j;
        before[i] = j;
        break;
      }
    }
  }
  parent[0][n] = n;
  for(int i = 0; i < n; i++) {
    int jump_to = nxt[i];
    if(jump_to != n) {
      jump_to = nxt[jump_to] - 1;
    }
    parent[0][i] = jump_to;
  }
  for(int i = 1; i < LOGN; i++) {
    for(int j = 0; j <= n; j++) {
      parent[i][j] = parent[i - 1][parent[i - 1][j]];
    }
  }

  for(int i = 0; i < n; i++) {
    int l = before[i];
    int r = i;
    for(int j = LOGN - 1; j >= 0; j--) {
      if(((1 << j) & (s - 1)) != 0) {
        r = parent[j][r];
      }
    }
    ll candidate = prefix[nxt[r] - 1] - (l == -1 ? 0 : prefix[l]);
    if(candidate > ans) {
      ans = candidate;
      ans_start = i;
    }
  }

  vector<int> Q;
  for(int i = 0; i < s; i++) {
    Q.push_back(ans_start);
    ans_start = parent[0][ans_start];
    if(ans_start == n)  break;
  }
  cout<<Q.size()<<endl;
  for(auto v : Q) cout<<v + 1<<" ";
  cout<<endl;
}
