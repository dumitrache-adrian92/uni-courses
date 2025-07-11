#include <bits/stdc++.h>
using namespace std;

#define INPUT_FILE "ferate.in"
#define OUTPUT_FILE "ferate.out"

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    // max number of nodes
    static constexpr int NMAX = (int)1e5 + 5;  // 10^5 + 5 = 100.005

    // n = node count, m = edge count, s = main deposit
    int n, m, s;

    // adj[node] = adjacency list of node
    vector<int> adj[NMAX];

    // parent[node] = parent of node in the DFS traversal
    vector<int> parent;

    // found[node] = the timestamp when node was found
    // (when started to visit its subtree)
    // Note: The global timestamp is incremented everytime a node is found.
    vector<int> found;

    // the minimum accessible timestamp that node can see/access
    // low_link[node] =  min { found[x] | x is node OR x in ancestors(node)
    // OR x in descendants(node) };
    vector<int> low_link;

    // visiting stack: nodes are pushed into the stack in visiting order
    stack<int> nodes_stack;

    // in_stack[node] = true, if node is in stack
    //                  false, otherwise
    vector<bool> in_stack;

    // scc_of[node] = the index of the scc that node is part of
    vector<int> scc_of;

    void read_input() {
        ifstream fin(INPUT_FILE);

        fin >> n >> m >> s;
        scc_of.resize(n + 1);

        for (int i = 1, x, y; i <= m; i++) {
            fin >> x >> y;
            adj[x].push_back(y);  // arc (x, y)
        }
        fin.close();
    }

    uint32_t get_result() {
        auto sccs = tarjan_scc();

        // vector which determines entry degree of each SCC
        vector<int> entry_degree(sccs.size(), 0);

        /* determine how many nodes have an entry degree of 0, this is done by
         * initially assuming that all SCCs are isolated and then iterating
         * through every single edge and decrementing the number of SCCs
         * with an entry degree of 0 whenever an edge is found that connects
         * an SCC that we previously though had an entry degree of 0 to another
         * SCC
         */

        uint32_t count = sccs.size() - 1;

        for (int node = 1; node <= n; node++)
            for (auto neigh : adj[node])
                if (scc_of[node] != scc_of[neigh]) {
                    if (entry_degree[scc_of[neigh]] == 0 &&
                            scc_of[neigh] != scc_of[s])
                        count--;

                    entry_degree[scc_of[neigh]]++;
                }

        return count;
    }

    vector<vector<int>> tarjan_scc() {
        // STEP 1: initialize results
        parent = vector<int>(n + 1, -1);
        found = vector<int>(n + 1, -1);
        low_link = vector<int>(n + 1, -1);
        in_stack = vector<bool>(n + 1, false);

        // STEP 2: visit all nodes
        vector<vector<int>> all_sccs;
        int timestamp = 0;  // global timestamp
        for (int node = 1; node <= n; ++node) {
            if (parent[node] == -1) {  // node not visited
                // convention: the parent of the root is actually the root
                parent[node] = node;

                // STEP 3: start a new DFS traversal this subtree
                dfs(node, timestamp, all_sccs);
            }
        }

        return all_sccs;
    }

    void dfs(int node, int& timestamp, vector<vector<int>>& all_sccs) {
        // STEP 1: a new node is visited - increment the timestamp
        found[node] = ++timestamp;  // the timestamp when node was found
        low_link[node] = found[node];  // node only knows its timestamp
        nodes_stack.push(node);  // add node to the visiting stack
        in_stack[node] = true;

        // STEP 2: visit each neighbour
        for (auto neigh : adj[node]) {
            // STEP 3: check if neigh is already visited
            if (parent[neigh] != -1) {
                // STEP 3.1: update low_link[node] with information gained
                // through neigh
                // note: neigh is in the same SCC with node only
                // if it's in the visiting stack;
                // otherwise, neigh is from other SCC, so it should be ignored
                if (in_stack[neigh]) {
                    low_link[node] = min(low_link[node], found[neigh]);
                }
                continue;
            }

            // STEP 4: save parent
            parent[neigh] = node;

            // STEP 5: recursively visit the child subree
            dfs(neigh, timestamp, all_sccs);

            // STEP 6: update low_link[node] with neigh info
            low_link[node] = min(low_link[node], low_link[neigh]);
        }

        // STEP 7: node is root in a SCC if low_link[node] == found[node]
        // (there is no edge from a descendant to an ancestor)
        if (low_link[node] == found[node]) {
            // STEP 7.1: pop all elements above node from stack =>
            // extract the SCC where node is root
            vector<int> scc;
            do {
                auto x = nodes_stack.top();
                nodes_stack.pop();
                in_stack[x] = false;

                scc_of[x] = all_sccs.size();
                scc.push_back(x);
            } while (scc.back() != node);
            // stop when node was popped from the stack

            // STEP 7.2: save SCC
            all_sccs.push_back(scc);
        }
    }

    void print_output(uint32_t count) {
        ofstream fout(OUTPUT_FILE);

        fout << count;

        fout.close();
    }
};

// [ATENTIE] NU modifica functia main!
int main() {
    // * se aloca un obiect Task pe heap
    // (se presupune ca e prea mare pentru a fi alocat pe stiva)
    // * se apeleaza metoda solve()
    // (citire, rezolvare, printare)
    // * se distruge obiectul si se elibereaza memoria
    auto* task = new (nothrow) Task();  // hint: cppreference/nothrow
    if (!task) {
        cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}
