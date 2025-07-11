#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    vector<int> numbas;
    unordered_map<int, bool> visited;

    cin >> n;

    for (int i = 0, x; i < n; i++) {
        cin >> x;
        numbas.push_back(x);
    }

    int src, tgt;
    queue<pair<int, int>> q;

    cin >> src >> tgt;
    q.push({src, 0});
    visited[src] = true;

    int distTgt = -1;

    while (!q.empty()) {
        auto [plm, ops] = q.front();

        if (plm == tgt) {
            distTgt = ops;
            break;
        }

        q.pop();

        for (auto numba : numbas) {
            if (plm + numba >= -20000 && plm + numba <= 20000) {
                if (visited.find(plm + numba) == visited.end()) {
                    visited[plm + numba] = true;
                    q.push({plm + numba, ops + 1});
                }
            }

            if (plm - numba >= -20000 && plm - numba <= 20000) {
                if (visited.find(plm - numba) == visited.end()) {
                    visited[plm - numba] = true;
                    q.push({plm - numba, ops + 1});
                }
            }
        }
    }

    cout << distTgt << endl;

    return 0;
}