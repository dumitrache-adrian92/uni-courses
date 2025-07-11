#include <bits/stdc++.h>
using namespace std;

struct Object {
    int weight;
    int price;
    float price_to_weight_ratio;

    Object(int _weight, int _price)
        : weight(_weight)
        , price(_price) {
            price_to_weight_ratio = (float) price / weight;
        }
};

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    int n, w;
    vector<Object> objs;

    void read_input() {
        ifstream fin("in");
        fin >> n >> w;
        for (int i = 0, weight, price; i < n; i++) {
            fin >> weight >> price;
            objs.push_back(Object(weight, price));
        }
        fin.close();
    }

    static bool ratio_cmp(Object &o1, Object &o2) {
        return (o1.price_to_weight_ratio > o2.price_to_weight_ratio);
    }

    double get_result() {
        // TODO: Aflati profitul maxim care se poate obtine cu obiectele date.
        sort(objs.begin(), objs.end(), ratio_cmp);

        for (Object o:objs)
            cout << o.price_to_weight_ratio << " ";

        int current_weight = 0;
        float current_profit = 0;
        int i = 0;

        while(current_weight < w && i < n) {
            if (current_weight + objs[i].weight > w) {
                int fraction = w - current_weight;
                current_weight += fraction;
                current_profit += (float) (fraction * objs[i].price) / objs[i].weight;
            } else {
                current_profit += objs[i].price;
                current_weight += objs[i].weight;
            }
            i++;
        }

        return current_profit;
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
