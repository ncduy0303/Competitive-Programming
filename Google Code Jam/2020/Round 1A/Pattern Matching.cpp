/*
Notice that the answer to the set of strings (starting with * and ending with *) is just a combination of all the strings in between

Example:
*abc*de*f*
*gh*
*i*j*
=> Answer is just "abcdefghij"

So we just need to find a way to deal with the prefix & suffix until the first * of each string
*/

#include <bits/stdc++.h>

using namespace std;

void solve() {
    int N; cin >> N;
    string str[N], pre[N], suf[N];
    int lp = 0, ls = 0;
    for (int i = 0; i < N; i++) {
        cin >> str[i];
        pre[i] = suf[i] = "";
        // remove prefix and suffix of p[i] without '*'
        for (; str[i].front() != '*'; str[i].erase(str[i].begin()))
            pre[i] = pre[i] + str[i].front();
        for (; str[i].back() != '*'; str[i].erase(str[i].end() - 1))
            suf[i] = str[i].back() + suf[i];
        // find longest prefix & suffix
        if (pre[i].size() > pre[lp].size()) lp = i;
		if (suf[i].size() > suf[ls].size()) ls = i;
    }

    // check whether all prefixes & suffixes match with the longest one
    for (int i = 0; i < N; i++) {
        if (pre[lp].substr(0, pre[i].size()) != pre[i] || suf[ls].substr(suf[ls].size() - suf[i].size()) != suf[i]) {
		cout << "*\n";
		return;
	}
    }

    // build the answer
    string ans = pre[lp];
    for (int i = 0; i < N; i++)
        for (char c : str[i])
            if (c != '*') ans += c;
    ans += suf[ls];
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
