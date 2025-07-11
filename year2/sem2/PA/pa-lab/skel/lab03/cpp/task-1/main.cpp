#include <bits/stdc++.h>
using namespace std;

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    int n, S;
    vector<int> v;

    void read_input() {
        ifstream fin("in");
        fin >> n >> S;
        v.push_back(-1); // adaugare element fictiv - indexare de la 1
        for (int i = 1, e; i <= n; i++) {
            fin >> e;
            v.push_back(e);
        }
        fin.close();
    }

    int get_result() {
        // TODO: Aflati numarul minim de monede ce poate fi folosit pentru a obtine
        // suma S. Tipurile monedelor sunt stocate in vectorul v, de dimensiune n.
        vector<int> dp(S + 1);

        fill(dp.begin(), dp.end(), 1000);

        dp[0] = 0;

        for (int j = 1; j <= n; j++)
            for (int i = 0; i <= S; i++)
                if (i - v[j] >= 0)
                    dp[i] = min(dp[i], dp[i - v[j]] + 1);

        if (dp[S] == 1000)
            return -1;

        return dp[S];
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
