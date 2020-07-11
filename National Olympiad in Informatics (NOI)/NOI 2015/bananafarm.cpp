/* NOI 2015: Banana Farm
Idea: Merge Sort Tree (basically a Segment Tree with each node containing a sorted vector of elements) (for range order statistics)
Time Complexity: O(N*logN) to build and O(logN*logN) for each query
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

int N, Q, arr[MAX_N];
pair<int, int> arr2[MAX_N]; // {element, index}
vector<int> st[4 * MAX_N];

// Building the merge sort tree (using zero-indexed)
void build(int node, int start, int end) {
    if(start == end) {
        st[node].push_back(arr2[start].second);
        return;
    }
    else {
        int mid = (start + end) / 2;
        build(2 * node + 1, start, mid);
        build(2 * node + 2, mid + 1, end);

        // Built-in merge function (takes two sorted arrays and merge them into a sorted array
        merge(st[2 * node + 1].begin(), st[2 * node + 1].end(),
              st[2 * node + 2].begin(), st[2 * node + 2].end(),
              back_inserter(st[node]));
    }
}

int query(int node, int start, int end, int l, int r, int k) { //k-th smallest element in [l..r]
    // Base case
    if(start == end) return st[node][0];

    int p = upper_bound(st[2 * node + 1].begin(), st[2 * node + 1].end(), r)
            - lower_bound(st[2 * node + 1].begin(), st[2 * node + 1].end(), l);

    int mid = (start + end) / 2;
    if(p >= k) return query(2 * node + 1, start, mid, l, r, k);
    else return query(2 * node + 2, mid + 1, end, l, r, k - p);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> N >> Q;
    for(int i = 0; i < N; i++) {
        cin >> arr[i];
        arr2[i] = {arr[i], i};
    }
    sort(arr2, arr2 + N); // We will build our segment tree based on the sorted index of the elements

    build(0, 0, N - 1);

    while(Q--) { // find the k-th largest element in [l..r]
        int l, r, k; cin >> l >> r >> k;
        l--; r--;
        k = r - l + 2 - k; // convert from finding k-th max to finding k-th min
        cout << arr[query(0, 0, N - 1, l, r, k)] << "\n";
    }
}

