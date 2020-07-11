/* NOI 2019: Rigged Road
Idea: use UFDS to ensure that only unlabeled edges are enumerated when an entire path has to be labeled
Time Complexity: O(ElogE)
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

int V, E, ss, sa, s, rx, ry;
int par_node[MAX_N], par_edge[MAX_N], par_edge_id[MAX_N], depth[MAX_N], a[MAX_N];
int vis[MAX_N], st[MAX_N], mst_s[MAX_N], ans[MAX_N], in_mst[MAX_N];
pair<int, int> EdgeList[MAX_N], mst_e[MAX_N];

int root(int x) {
	int p = x, q = x, r;
	while (p != par_node[p])
    p = par_node[p];
	while (q != p) {
		r = par_node[q];
		par_node[q] = p;
		q = r;
	}
	return p;
}

void merge_edge(int id) {
	ans[id] = s++;
	if (par_edge[EdgeList[id].first] == EdgeList[id].second)
		par_node[EdgeList[id].first] = root(EdgeList[id].second);
	else
		par_node[EdgeList[id].second] = root(EdgeList[id].first);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    //read input and create mapping of edge to index
    cin >> V >> E;
    for (int i = 0; i < E; i++) cin >> EdgeList[i].first >> EdgeList[i].second;

    // construct MST by letting 1 as the root, using explicit stack and backtracking
    memset(par_edge, 0, sizeof par_edge);
	  memset(in_mst, 0, sizeof in_mst);
	  memset(mst_s, 0, sizeof mst_s);
    for (int i = 0; i < V - 1; i++) {
		  int x; cin >> x; x--;
		  in_mst[x] = 1;
		  mst_e[i * 2] = mst_e[i * 2 + 1] = EdgeList[x];
		  swap(mst_e[i * 2].first, mst_e[i * 2].second);
		  mst_s[EdgeList[x].first]++;
		  mst_s[EdgeList[x].second]++;
	  }
	  sort(mst_e, mst_e + 2 * V - 2);
    for (int i = 1; i <= V; i++)
		mst_s[i] += mst_s[i - 1];

    memset(vis, 0, sizeof vis);
    st[1] = 1;
	  vis[1] = 1;
	  depth[1] = 1;
	  ss = 1;
	  while (ss) {
		  int i = st[ss--];
		  for (int j = mst_s[i - 1]; j < mst_s[i]; j++) {
			  if (!vis[mst_e[j].second]) {
				  st[++ss] = mst_e[j].second;
				  vis[mst_e[j].second] = 1;
				  par_edge[mst_e[j].second] = i;
				  depth[mst_e[j].second] = depth[i] + 1;
			  }
		  }
	  }
	  for (int i = 0; i < E; i++) {
		  if (par_edge[EdgeList[i].first] == EdgeList[i].second)
			  par_edge_id[EdgeList[i].first] = i;
		  else if (par_edge[EdgeList[i].second] == EdgeList[i].first)
			  par_edge_id[EdgeList[i].second] = i;
	  }

	  //sequentially assign weights
	  for (int i = 1; i <= V; i++)
		  par_node[i] = i;

    s = 1;
    memset(ans, 0, sizeof ans);
	  for (int i = 0; i < E; i++) {
		  if (in_mst[i]) // if edge i in mst and not assigned weight, assign next weight and merge with its parent
			  if (!ans[i])
				  merge_edge(i);
		  else { // find LCA and push all unlabeled edge into vector a
			  rx = root(EdgeList[i].first), ry = root(EdgeList[i].second);
			  sa = 0;
			  while (rx != ry) {
				  if (depth[rx] > depth[ry]) {
					  a[sa++] = par_edge_id[rx];
					  rx = root(par_edge[rx]);
				  }
				  else {
					  a[sa++] = par_edge_id[ry];
					  ry = root(par_edge[ry]);
				  }
			  }
			  //assign next weight to sorted values in a, and then edge i
			  sort(a, a + sa);
			  for (int j = 0; j < sa; j++)
				  merge_edge(a[j]);
			  ans[i] = s++;
			  // merge all nodes along the 2 paths
			  ry = root(EdgeList[i].first);
			  while (ry != rx) {
				  int j = par_node[ry];
				  par_node[ry] = rx;
				  ry = j;
			  }
			  ry = root(EdgeList[i].second);
			  while (ry != rx) {
				  int j = par_node[ry];
				  par_node[ry] = rx;
				  ry = j;
			  }
		  }
	  }
	  for (int i = 0; i < V; i++)
		  cout << ans[i] << " ";
}
