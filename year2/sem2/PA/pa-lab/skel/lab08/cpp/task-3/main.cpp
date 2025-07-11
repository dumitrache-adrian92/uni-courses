#include <bits/stdc++.h>
using namespace std;

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    struct Edge {
        int x;
        int y;

        Edge() { }
        Edge(int x, int y)
            : x(x)
            , y(y) { }
    };

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
            fin >> x >> y; // muchia (x, y)
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
        fin.close();
    }

    void dfs(int node, vector<int> &parent, vector<int> &found, vector<int> &low_link, int &timestamp, vector<Edge> &all_ces) {
        timestamp++;
        found[node] = timestamp;
        low_link[node] = found[node];

        for (auto neigh : adj[node]) {
            if (parent[neigh] != -1) {
                if (neigh != parent[node])
                    low_link[node] = min(low_link[node], found[neigh]);

                continue;
            }

            parent[neigh] = node;

            dfs(neigh, parent, found, low_link, timestamp, all_ces);

            low_link[node] = min(low_link[node], low_link[neigh]);

            if (low_link[neigh] > found[node])
                all_ces.push_back(Edge(node, neigh));
        }
    }

    vector<Edge> get_result() {
        //
        // TODO: Gasiti toate muchiile critice ale grafului neorientat stocat cu liste de adiacenta in adj.
        //
        // Rezultatul se va returna sub forma unui vector cu toate muchille critice (ordinea lor nu conteaza).
        //
        // Indicație: Folosiți algoritmul lui Tarjan pentru CE.
        //
        vector<Edge> all_ces;

        vector<int> parent(n + 1, -1);
        vector<int> found(n + 1, -1);
        vector<int> low_link(n + 1, -1);

        int timestamp = 0;

        for (int i = 1; i <= n; i++) {
            if (found[i] == -1) {
                parent[i] = i;

                dfs(i, parent, found, low_link, timestamp, all_ces);
            }
        }

        return all_ces;
    }

    void print_output(const vector<Edge>& all_ces) {
        ofstream fout("out");
        fout << all_ces.size() << '\n';
        for (auto& ce : all_ces) {
            fout << ce.x << ' ' << ce.y << '\n';
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
