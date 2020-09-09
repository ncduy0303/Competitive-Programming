// Reference: https://codeforces.com/blog/entry/11080, https://www.geeksforgeeks.org/ordered-set-gnu-c-pbds/

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
/*
1. int : It is the type of the data that we want to insert (KEY).It can be integer, float or pair of int etc.
2. null_type : It is the mapped policy. It is null here to use it as a set. If we want to get map but not the set, as the second argument type must be used mapped type.
3. less<int> : It is the basis for comparison of two functions (others available function include less_equal, etc.)
4. rb_tree_tag : type of tree used. It is generally Red black trees because it takes log(n) time for insertion and deletion while other take linear time such as splay_tree.
5. tree_order_statistics_node__update : It is included in <tree_policy.hpp> and contains various operations for updating the node variants of a tree-based container, so we can keep track of metadata like the number of nodes in a subtree

Can perform the same operations as C++ STL set, with the addition of other extra functions in O(logn):
1. order_of_key (k) : number of items strictly smaller than k
2. find_by_order(k) : returns the iterator of the k-th element in a set (counting from zero) (in sorted order)
*/

// Application: https://cses.fi/problemset/task/1144
// With the use of ordered_set, the code is much more concise and simpler

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int n, q; cin >> n >> q;
    int arr[n];
    ordered_set s;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        s.insert(arr[i]);
    }
    while (q--) {
        char c; int x, y; cin >> c >> x >> y;
        if (c == '?') // count the number of elements between x and y
            cout << s.order_of_key(y + 1) - s.order_of_key(x) << "\n";
        else {
            x--;
            s.erase(s.find_by_order(s.order_of_key(arr[x])));
            arr[x] = y;
            s.insert(y);
        }
    }
}

