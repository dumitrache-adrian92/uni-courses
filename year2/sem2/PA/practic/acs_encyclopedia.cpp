#include <bits/stdc++.h>

using namespace std;

#define NMAX 10005

int dfs(int node, vector<int> adj[], int n, vector<int> &visited)
{
    int length = 1;

    visited[node] = 1;

    for (auto i : adj[node]) {
        if (visited[i] == 0) {
            length += dfs(i, adj, n, visited);
        }
    }

    return length;
}

int main(void)
{
    int n;

    cin >> n;

    vector<int> adj[NMAX];
    vector<int> visited(n + 1, 0);

    for (int i = 1, x; i <= n; i++) {
        cin >> x;

        adj[i].push_back(x);
    }

    int max = dfs(1, adj, n, visited);

    for (int i = 2; i <= n; i++) {
        visited = vector<int>(n + 1, 0);

        int length = dfs(i, adj, n, visited);

        if (length > max)
            max = length;
    }

    cout << max;

    return 0;
}