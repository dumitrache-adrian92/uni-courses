#include <bits/stdc++.h>
using namespace std;

// constanta modulo folosita in aceasta problema
#define MOD ((int)1e9 + 7)
// sau
// #define MOD 100000007
// (varianta 2 e mai ușor de busit, sesizați? :p)

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    int n;
    vector<int> v;

    void read_input() {
        ifstream fin("in");
        fin >> n;
        v.push_back(-1); // adaugare element fictiv - indexare de la 1
        for (int i = 1, e; i <= n; i++) {
            fin >> e;
            v.push_back(e);
        }
        fin.close();
    }

    int get_result() {
        // Calculati numarul de subsiruri ale lui v cu suma numerelor para si
        // returnati restul impartirii numarului la 10^9 + 7 (vezi macro-ul MOD).
        vector<unsigned long long> dp_par(n + 1);
        vector<unsigned long long> dp_impar(n + 1);
        dp_par[0] = 0;
        dp_impar[0] = 0;

        for (int i = 1; i <= n; i++)
            if (v[i] & 1) {
                dp_par[i] = (dp_impar[i - 1] % MOD + dp_par[i - 1] % MOD) % MOD;
                dp_impar[i] = (dp_par[i - 1] % MOD + dp_impar[i - 1] % MOD + 1 % MOD) % MOD;
            } else {
                dp_par[i] = (dp_par[i - 1] % MOD +  dp_par[i - 1] % MOD + 1 % MOD) % MOD;
                dp_impar[i] = (dp_impar[i - 1] % MOD + dp_impar[i - 1] % MOD) % MOD;
            }

        return dp_par[n];
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
