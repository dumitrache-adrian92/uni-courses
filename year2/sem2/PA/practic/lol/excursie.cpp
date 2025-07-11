#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, k;

    cin >> n >> k;

    vector<vector<int>> da_matrix(n + 1, vector<int>(n+1));
    vector<vector<int>> visited(n + 1, vector<int>(n+1, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> da_matrix[i][j];
        }
    }

    queue<tuple<int, int, int, int>> q;

    q.push({0, 0, 1, da_matrix[0][0]});

    int min = INT_MAX;

    while (!q.empty()) {
        auto [x, y, level, cost] = q.front();
        q.pop();

        if (level >= k && min > cost) {
            min = cost;
            continue;
        }

        if (cost > k * 100 || level > 2 * n - 1)
            continue;

        if (x + 1 < n && y + 1 < n)
            q.push({x + 1, y + 1, level + 1, cost + da_matrix[x + 1][y + 1]});
        if (x + 1 < n)
            q.push({x + 1, y, level + 1, cost + da_matrix[x + 1][y]});
        if (y + 1 < n)
            q.push({x, y + 1, level + 1, cost + da_matrix[x][y + 1]});
    }

    cout << min;

    return 0;
}