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
    int n, x;

    // adj[node] = lista de adiacenta a nodului node
    // exemplu: daca adj[node] = {..., neigh, ...} => exista muchia (node, neigh)
    vector<int> adj[NMAX];
    vector<int> in_degree;
    vector<int> important;
    vector<int> is_important;
    vector<vector<int>> dependencies;

    void read_input() {
        cin >> n >> x;
        in_degree.resize(n + 1, 0);
        dependencies.resize(n + 1);
        is_important.resize(n + 1, 0);

        for (int i = 0, a; i < x; i++) {
            cin >> a;
            important.push_back(a);
            is_important[a] = 1;
        }

        for (int i = 1, count; i <= n; i++) {
           cin >> count;

           for (int j = 0, a; j < count; j++) {
                cin >> a;
                adj[a].push_back(i);
                in_degree[i]++;

                dependencies[i].push_back(a);
           }
        }

        for (uint32_t i = 0; i < important.size(); i++) {
            for (auto dep : dependencies[important[i]]) {
                if (is_important[dep] == 0) {
                    important.push_back(dep);
                    is_important[dep] = 1;
                }
            }
        }
    }

    vector<int> get_result() {
        vector<int> topsort;
        queue<int> q;

        for (int i = 1; i <= n; i++)
            if (in_degree[i] == 0)
                q.push(i);

        while(!q.empty()) {
            int node = q.front();

            if (is_important[node] == 1)
                topsort.push_back(node);

            for (auto neigh : adj[node]) {
                in_degree[neigh]--;

                if (in_degree[neigh] == 0)
                    q.push(neigh);
            }

            q.pop();
        }

        for (auto deg : in_degree)
            if (deg != 0)
                return vector<int>(1, -1);

        return topsort;
    }

    void print_output(vector<int> d) {
        if (d[0] == -1) {
            cout << -1;
            return;
        } else {
            sort(d.begin(), d.end());

            cout << d.size() << '\n';

            for (auto imp : d) {
                cout << imp << ' ';
            }
        }
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
