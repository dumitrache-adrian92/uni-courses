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
    string expr;

    void read_input() {
        ifstream fin("in");
        fin >> n >> expr;
        expr = " " + expr; // adaugare caracter fictiv - indexare de la 1
        fin.close();
    }

    int get_result() {
        // Calculati numarul de parantezari ale expresiei date astfel incat
        // rezultatul sa dea true si returnati restul impartirii numarului
        // la 10^9 + 7 (vezi macro-ul MOD).
        int elem_count = n / 2 + 1;
        int op_cout = n / 2;

        vector<vector<int>> dp_true(elem_count + 1, vector<int>(elem_count + 1, 0));
        vector<vector<int>> dp_false(elem_count + 1, vector<int>(elem_count + 1, INF));

        for (int i = 0; i <= elem_count; i++) {
            dp_true[i][i] = 1;
            dp_false[i][i] = 1;
        }

        for (int i = 1; i < elem_count; i++) {
            if ()
            dp_true[i][i + 1] =
        }

        for (int i = 1; i <= elem_count; i++) {
            for (int j = 1; j < elem_count; j++) {
                for (int k = j; k < j; k++) {

                }
            }
        }

        return dp[0][elem_count - 1] % MOD;
    }

    void print_output(int result) {
        ofstream fout("out");
        fout << result << '\n';
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
