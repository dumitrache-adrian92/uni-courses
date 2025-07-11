#include <bits/stdc++.h>
using namespace std;

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    int n, m;
    vector<int> dist;

    void read_input() {
        ifstream fin("in");
        fin >> n >> m;
        for (int i = 0, d; i < n; i++) {
            fin >> d;
            dist.push_back(d);
        }
        fin.close();
    }

    int get_result() {
        // TODO: Aflati numarul minim de opriri necesare pentru a ajunge
        // la destinatie.
        int fuel = m;
        int stops = 0;
        dist.insert(dist.begin(), 0);

        for (int i = 1; i < dist.size() - 1; i++) {
            fuel -= dist[i] - dist[i - 1];
            if (fuel - (dist[i + 1] - dist[i]) < 0) {
                stops++;
                fuel = m;
            }
        }

        return stops;
    }

    void print_output(int result) {
        ofstream fout("out");
        fout << result;
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
