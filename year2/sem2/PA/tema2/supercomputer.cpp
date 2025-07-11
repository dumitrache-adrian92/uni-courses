#include <bits/stdc++.h>
using namespace std;

#define INPUT_FILE "supercomputer.in"
#define OUTPUT_FILE "supercomputer.out"

class Supercomputer {
 public:
    void solve() {
        ofstream fout(OUTPUT_FILE);

        read_input();
        fout << get_result();
        fout.close();
    }

 private:
    // maximum number of nodes
    static constexpr int NMAX = (int)1e5 + 5;  // 10^5 + 5 = 100.005

    // node count and edge count
    int n, m;

    // adjacency list
    vector<int> adj[NMAX];
    // which data set is required for each node
    vector<int> data_required;
    // entry degree of each node
    vector<int> entry_degree;

    // reads all input from file
    void read_input() {
        ifstream fin(INPUT_FILE);

        fin >> n >> m;
        data_required.resize(n + 1);
        entry_degree.resize(n + 1);

        for (int i = 1, x; i <= n; i++) {
            fin >> x;
            data_required[i] = x;
        }

        for (int i = 1, x, y; i <= m; i++) {
            fin >> x >> y;
            // we'll be representing the task dependencies as a graph
            adj[x].push_back(y);
            // and compute the entry degree of each node
            entry_degree[y]++;
        }

        fin.close();
    }

    vector<int> get_topsort(queue<int> q1, queue<int> q2,
                            vector<int> entry_deg, int q1_group) {
        vector<int> topsort;

        while (!q1.empty() || !q2.empty()) {
            // start by "running" the tasks in the first queue
            while (!q1.empty()) {
                int node = q1.front();
                q1.pop();

                topsort.push_back(node);

                /* check if any of the node neighbors no longer have
                 * dependencies and add them to their respective queue
                 */
                for (auto neigh : adj[node]) {
                    entry_deg[neigh]--;

                    if (entry_deg[neigh] == 0) {
                        if (data_required[neigh] == q1_group)
                            q1.push(neigh);
                        else
                            q2.push(neigh);
                    }
                }
            }

            /* once there are no other tasks to run in the first queue
             * we have no choice but to make a context switch and start running
             * the tasks in the second queue
             * */
            while (!q2.empty()) {
                int node = q2.front();
                q2.pop();

                topsort.push_back(node);

                for (auto neigh : adj[node]) {
                    entry_deg[neigh]--;

                    if (entry_deg[neigh] == 0) {
                        if (data_required[neigh] == q1_group)
                            q1.push(neigh);
                        else
                            q2.push(neigh);
                    }
                }
            }
        }

        return topsort;
    }

    /* we'll be using a sort of BFS that prioritizes the exploration of nodes
     * that are part of the same data set as the current and leaves the others
     * for later so as to minimize the amount of context switching, Kahn's algo
     * isn't necessary for this problem since we are guaranteed to receive a
     * graph that can be represented as a topological sort (no cycles)
     */
    uint32_t get_result() {
        // queue of nodes with data set 1 or 2
        queue<int> q1, q2;

        /* enqueue all nodes with have an entry degree of 0, meaning tasks that
         * can be executed directly
         */
        for (int i = 1; i <= n; i++)
            if (entry_degree[i] == 0) {
                if (data_required[i] == 1)
                    q1.push(i);
                else
                    q2.push(i);
            }

        /* there's no way to determine which data set we should start with
         * so we'll try starting with both of them and compare the results
         */

        // get topological sort starting with data set 1
        uint32_t switches1 = 0;
        vector<int> topsort1 = get_topsort(q1, q2, entry_degree, 1);

        // compute the amount of context switches
        for (int i = 0; i <= n - 2; i++)
            if (data_required[topsort1[i]] != data_required[topsort1[i + 1]])
                switches1++;

        // get topological sort starting with data set 2
        uint32_t switches2 = 0;
        vector<int> topsort2 = get_topsort(q2, q1, entry_degree, 2);

        // compute the amount of context switches
        for (int i = 0; i <= n - 2; i++)
            if (data_required[topsort2[i]] != data_required[topsort2[i + 1]])
                switches2++;

        // return the best variant
        return min(switches1, switches2);
    }
};

int main() {
    // solve the problem in a heap allocated object so we avoid stack overflow
    auto* task = new (nothrow) Supercomputer();
    if (!task) {
        cerr << "RIP\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}
