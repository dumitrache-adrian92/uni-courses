#include <bits/stdc++.h>

using namespace std;

#define NMAX 10005

bool visited[NMAX][NMAX];

int main()
{
    int n, m, p, src_x, src_y;

    cin >> n >> m >> p >> src_x >> src_y;

    int da_matrix[n + 1][m + 1];

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> da_matrix[i][j];

    queue<tuple<int, int, int>> q;

    q.push({src_x, src_y, 0});

    int max = da_matrix[src_x][src_y];

    while (!q.empty()) {
        auto [x, y, level] = q.front();
        q.pop();

        if (da_matrix[x][y] > max)
            max = da_matrix[x][y];

        if (level >= p || visited[x][y])
            continue;

        visited[x][y] = true;

        if (x + 1 <= n)
            q.push({x + 1, y, level + 1});

        if (x - 1 >= 1)
            q.push({x - 1, y, level + 1});

        if (y + 1 <= m)
            q.push({x, y + 1, level + 1});

        if (y - 1 >= 1)
            q.push({x, y - 1, level + 1});
    }

    cout << max;

    return 0;
}