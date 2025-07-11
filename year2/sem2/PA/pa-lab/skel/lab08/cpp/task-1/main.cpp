#include <bits/stdc++.h>
using namespace std;

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    // numarul maxim de noduri
    static constexpr int NMAX = (int)1e5 + 5; // 10^5 + 5 = 100.005

    // n = numar de noduri, m = numar de muchii/arce
    int n, m;

    // adj[node] = lista de adiacenta a nodului node
    // exemplu: daca adj[node] = {..., neigh, ...} => exista arcul (node, neigh)
    vector<int> adj[NMAX];

    void read_input() {
        ifstream fin("in");
        fin >> n >> m;
        for (int i = 1, x, y; i <= m; i++) {
            fin >> x >> y;
            adj[x].push_back(y); // arc (x, y)
        }
        fin.close();
    }

    void dfs(int node, vector<int> &parent, vector<int> &found, vector<int> &low_link, vector<int> &stack, int &timestamp, vector<vector<int>> &all_sccs) {
        timestamp++;
        found[node] = timestamp;
        low_link[node] = found[node];
        stack.push_back(node);

        for (auto neigh : adj[node]) {
            if (parent[neigh] != -1) {
                if (find(stack.begin(), stack.end(), neigh) != stack.end())
                    low_link[node] = min(low_link[node], found[neigh]);

                continue;
            }

            parent[neigh] = node;

            dfs(neigh, parent, found, low_link, stack, timestamp, all_sccs);

            low_link[node] = min(low_link[node], low_link[neigh]);
        }

        if (low_link[node] == found[node]) {
            vector<int> scc;

            do {
                scc.push_back(stack.back());
                stack.pop_back();
            } while (scc.back() != node);

            all_sccs.push_back(scc);
        }
    }

    vector<vector<int>> get_result() {
        //
        // TODO: Găsiți componentele tare conexe  (CTC / SCC) ale grafului orientat cu n noduri, stocat în adj.
        //
        // Rezultatul se va returna sub forma unui vector, fiecare element fiind un SCC (adică tot un vector).
        // * nodurile dintr-un SCC pot fi găsite în orice ordine
        // * SCC-urile din graf pot fi găsite în orice ordine
        //
        // Indicație: Folosiți algoritmul lui Tarjan pentru SCC.
        //

        vector<vector<int>> all_sccs;

        vector<int> parent(n + 1, -1);
        vector<int> found(n + 1, -1);
        vector<int> low_link(n + 1, -1);
        vector<int> st;

        int timestamp = 0;

        for (int i = 1; i <= n; i++) {
            if (found[i] == -1) {
                parent[i] = i;

                dfs(i, parent, found, low_link, st, timestamp, all_sccs);
            }
        }

        return all_sccs;
    }

    void print_output(const vector<vector<int>>& all_sccs) {
        ofstream fout("out");
        fout << all_sccs.size() << '\n';
        for (const auto& scc : all_sccs) {
            for (auto node : scc) {
                fout << node << ' ';
            }
            fout << '\n';
        }
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
    auto* task = new (nothrow) Task(); // hint: cppreference/nothrow
    if (!task) {
        cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}
