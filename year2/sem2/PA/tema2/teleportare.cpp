#include <bits/stdc++.h>

using namespace std;

#define INPUT_FILE "teleportare.in"
#define OUTPUT_FILE "teleportare.out"
#define NMAX 50005
#define INF (1 << 30)

struct DijkstraResult {
    vector<int> d;
    vector<int> p;

    DijkstraResult(const vector<int>& d, const vector<int>& p)
        : d(d)
        , p(p) { }
};

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    // n = node count, m = regular edge count, k = teleport edge count
    int n, m, k;
    // adj[node] = {neighbor, weight, period}
    vector<tuple<int, int, int>> adj[NMAX];
    // start node
    int source = 1;

    void read_input() {
        ifstream fin(INPUT_FILE);

        fin >> n >> m >> k;

        // construct the graph, non teleport edges will have a period of 0
        for (int i = 1, x, y, w; i <= m; i++) {
            fin >> x >> y >> w;
            adj[x].push_back({y, w, 0});
            adj[y].push_back({x, w, 0});
        }

        for (int i = 1, x, y, p; i <= k; i++) {
            fin >> x >> y >> p;
            adj[x].push_back({y, 1, p});
            adj[y].push_back({x, 1, p});
        }

        fin.close();
    }

    vector<int> get_result() {
        return dijkstra(source, n);
    }

    vector<int> dijkstra(int source, int nodes) {
        // keep track of distances as the algorithm progresses
        vector<int> d(nodes + 1, INF);
        set<pair<int, int>> pq;

        // start from the source node
        d[source] = 0;
        pq.insert({d[source], source});

        while (!pq.empty()) {
            auto top = pq.begin();
            const auto [time, node] = *top;

            pq.erase(top);

            // if we've reached the destination, we can stop
            if (node == n)
                break;

            // parse every neighbor of the current node
            for (const auto& [neigh, w, period] : adj[node]) {
                /* check if we can use this edge or not based on the
                 * time when the node was reached
                 */
                if (period != 0 && time % period == 0) {
                    if (time + w < d[neigh]) {
                        pq.erase({d[neigh], neigh});

                        d[neigh] = time + w;

                        pq.insert({time + w, neigh});
                    }
                } else if (period == 0) {
                    if (d[node] + w < d[neigh]) {
                        pq.erase({d[neigh], neigh});

                        d[neigh] = d[node] + w;

                        pq.insert({d[node] + w, neigh});
                    }
                }
            }
        }

        return d;
    }

    void print_output(const vector<int>& result) {
        ofstream fout(OUTPUT_FILE);

        fout << result[n];

        fout.close();
    }
};

int main() {
    // avoid stack overflow
    auto* task = new (nothrow) Task();  // hint: cppreference/nothrow
    if (!task) {
        cerr << "RIP\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}
