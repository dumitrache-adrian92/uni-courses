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
    // exemplu: daca adj[node] = {..., neigh, ...} => exista muchia (node, neigh)
    vector<int> adj[NMAX];

    // nodul sursa in parcurgerea BFS
    int source = 1;

    void read_input() {
        cin >> n >> m;
        for (int i = 1, x, y; i <= m; i++) {
            cin >> x >> y; // muchie (x, y)
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
    }

    vector<int> get_result() {
        vector<int> d(n + 1, -1);
        queue<int> q;

        q.push(source);
        d[source] = 0;

        while(!q.empty()) {
            int node = q.front();

            for (auto neigh : adj[node])
                if (d[node] + 1 < d[neigh] || d[neigh] == -1) {
                    d[neigh] = d[node] + 1;
                    q.push(neigh);
                }

            q.pop();
        }


        return d;
    }

    void print_output(const vector<int>& d) {
        cout << *max_element(d.begin(), d.end());
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
