#include <bits/stdc++.h>

using namespace std;

#define NMAX 1005

double da_matrix[NMAX][NMAX];
bool visited[NMAX][NMAX];

int main()
{
    int n, m;

    cin >> n >> m;

    int src_x, src_y;
    int dst_x, dst_y;

    cin >> src_x >> src_y;
    cin >> dst_x >> dst_y;

    da_matrix[src_x][src_y] = 10000.0;

    queue<pair<int, int>> q;

    q.push({src_x, src_y});

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        if (visited[x][y])
            continue;

        visited[x][y] = true;

        double neigh_count = 0;

        vector<pair<int, int>> neighs;

        if (x + 1 < n) {
            neigh_count++;
            neighs.push_back({x + 1, y});
        }

        if (x - 1 >= 0) {
            neigh_count++;
            neighs.push_back({x - 1, y});
        }

        if (y + 1 < m) {
            neigh_count++;
            neighs.push_back({x, y + 1});
        }

        if (y - 1 >= 0) {
            neigh_count++;
            neighs.push_back({x, y - 1});
        }

        double prob = 1.0 * da_matrix[x][y] / neighs.size();

        for (auto [a, b] : neighs)
            if (!visited[a][b]) {
                da_matrix[a][b] += prob;
                q.push({a, b});
            }
    }

    cout << setprecision(4) << fixed << da_matrix[dst_x][dst_y];

    return 0;
}