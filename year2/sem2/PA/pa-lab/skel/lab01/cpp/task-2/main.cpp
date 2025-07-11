#include <bits/stdc++.h>
using namespace std;

class Task {
public:
    void solve() {
        read_input();
        if (n < 1)
            print_output(get_result(n, 0.01, 1));
        else print_output(get_result(n, 0.01, n));
    }

private:
    double n;

    void read_input() {
        ifstream fin("in");
        fin >> n;
        fin.close();
    }

    double get_result(double n, double left, double right) {
        // TODO: Calculati sqrt(n) cu o precizie de 0.001
        // Precizie de 10^-x = |rezultatul vostru - rezultatul corect| <= 10^-x

        double mid = (left + right) / 2;

        if (abs(mid * mid - n) <= 0.001)
            return mid;
        else if (mid * mid < n)
            return get_result(n, mid + 0.001, right);
        else
            return get_result(n, left, mid - 0.001);
    }

    void print_output(double result) {
        ofstream fout("out");
        fout << setprecision(4) << fixed << result;
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
