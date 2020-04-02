// Flood fill
// Direct application of DFS/BFS on implicit 2D graph
// Given some grid structure, we can perform traversal using DFS/BFS implicitly

/*
Example grid
Given N = 4, M = 5
...**
*.*..
**.*.
...*.
*/

#include <bits/stdc++.h>

using namespace std;

const int INF = 1 << 30;
const int MAX_N = 1000 + 5;
const int MAX_L = 20; // ~ Log N
const long long MOD = 1e9 + 7;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) (S & (-S))
#define isBitSet(S, i) ((S >> i) & 1)

int N, M, visited[MAX_N][MAX_N];
char grid[MAX_N][MAX_N];
int dr[] = {1, 1, 0, -1, -1, -1, 0, 1};
int dc[] = {0, 1 ,1, 1, 0, -1, -1, -1};

void floodfill (int r, int c) {
    if (r < 0 || c < 0 || r >= N || c >= M) return;
    if (visited[r][c] || grid[r][c] != '*') return;

    visited[r][c] = 1;
    for (int d = 0; d < 8; d++)
        floodfill(r + dr[r], c + dc[c]);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> N >> M;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> grid[i][j];

    memset(visited, 0, sizeof visited);
    for (int r = 0; r < N; r++)
        for (int c = 0; c < M; c++)
            floodfill(r, c);
}
