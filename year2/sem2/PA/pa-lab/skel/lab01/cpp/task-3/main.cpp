#include <bits/stdc++.h>
using namespace std;

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    int n, x, y;
    int number = 1;

    void read_input() {
        ifstream fin("in");
        fin >> n >> x >> y;
        fin.close();
    }

    int get_value(int n, int x, int y, int currX, int currY) {
        // TODO: Calculati valoarea de pe pozitia (x, y) din matricea de dimensiune 2^n x 2^n
        if (n > 1) {
            int upperLeft = get_value(n / 2, x, y, currX, currY);
            int lowerLeft = get_value(n / 2, x, y, currX, currY + n / 2);
            int upperRight = get_value(n / 2, x, y, currX + n / 2, currY);
            int lowerRight = get_value(n / 2, x, y, currX + n / 2, currY + n / 2);
            return upperLeft + upperRight + lowerLeft + lowerRight;
        } else if (n == 1) {
            if (x == currX && y == currY)
                return number++;
            else
                number++;
        }

        return 0;
    }

    int get_result() {
        int size = pow(2, n);
        return get_value(size, x - 1, y - 1, 0, 0);
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
