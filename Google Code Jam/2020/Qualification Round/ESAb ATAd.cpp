#include <bits/stdc++.h>

using namespace std;

int TC, B, arr[100]; // use 0-indexed
int same_pair, diff_pair; // record the latest same/different pairs, -1 means no such pairs have been found

// take note: must use endl instead of "\n" for interative problems

int query(int i) {
    cout << i + 1 << endl;
    int res; cin >> res;
    return res;
}

void find_pair(int i) {
    arr[i] = query(i);
    arr[B - i - 1] = query(B - i - 1);
    if (same_pair == -1 && arr[i] == arr[B - i - 1])
        same_pair = i;
    if (diff_pair == -1 && arr[i] != arr[B - i - 1])
        diff_pair = i;
}

void find_fluctuation() {
    bool comp = false;
    if (same_pair != - 1 && arr[same_pair] != query(same_pair)) // complement definitely occurred
        comp = true;
    bool rev = comp;
    if (diff_pair != - 1 && arr[diff_pair] != query(diff_pair)) // reverse occurred if complement didn't, and otherwise
        rev = !comp;

    // Modify the array
    if (comp)
        for (int i = 0; i < B; i++)
            arr[i] = !arr[i];
    if (rev)
        for (int i = 0; i < B / 2; i++)
            swap(arr[i], arr[B - i - 1]);
}

void solve() {
    // Initialize
    same_pair = diff_pair = -1;

    // Find 5 pairs using query 1st - 10th, fluctuation occurred before the 1st query
    int c = 0;
    for (; c < 5; c++)
        find_pair(c);
    // Use the next two queries to find fluctuations
    find_fluctuation();

    // Repeat this same process (8 queries to find 4 pairs && 2 queries to find fluctuations)
    while (c < B / 2) {
        int i = 0;
        for (; i < 4 && c < B / 2; i++, c++)
            find_pair(c);
        if (i == 4) // fluctuation only happens if all 8 queries happened
            find_fluctuation();
    }

    // Print out the answer
    for (int i = 0; i < B; i++)
        cout << arr[i];
    cout << endl;
    
    char ok; cin >> ok;
    if (ok == 'N') exit(0);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> TC >> B;
    for (int t = 1; t <= TC; t++)
        solve();
}
