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
        ifstream fin("dfs.in");
        fin >> n >> m;
        for (int i = 1, x, y; i <= m; i++) {
            fin >> x >> y; // arc (x, y)
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
        fin.close();
    }

    void dfs(int node, vector<int> &parent) {
        for (auto neigh : adj[node])
            if (parent[neigh] == -1) {
                parent[neigh] = node;
                dfs(neigh, parent);
            }
    }

    int get_result() {
        vector<int> parent(n + 1);
        int scc = 0;

        for (int i = 1; i <= n; i++)
            parent[i] = -1;

        for (int i = 1; i <= n; i++)
            if (parent[i] == -1) {
                parent[i] = -2;
                dfs(i, parent);

                scc++;
            }

        return scc;
    }

    void print_output(int scc) {
        ofstream fout("dfs.out");

        fout<<scc;

        fout << '\n';
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
        cerr << "new failed: WTF are you doing? Throw your PC! mean\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}
