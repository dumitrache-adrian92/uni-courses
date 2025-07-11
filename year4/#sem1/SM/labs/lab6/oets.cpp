#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <bits/stdc++.h>

using namespace std;

void display_vector(std::vector<int> v) {
    for (auto x : v) {
        cout << x << " ";
    }
    cout << std::endl;
}

void init_vector(std::vector<int> &v) {
    srand(42);

    for (auto &x : v) {
        x = rand() % 420;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <arr_len> <num_threads>\n", argv[0]);
        exit(1);
    }

    int n = atoi(argv[1]);
    int p = atoi(argv[2]);

    std::vector<int> v(n);

    init_vector(v);

    int phase, i, temp;
    bool sorted = false;

    #pragma omp parallel num_threads(p) default(none) shared(v,n) private(i,temp,phase)
    {
        for (phase = 0; phase < n; phase++) {
            if (phase % 2 == 0) {
                #pragma omp for
                    for (i = 1; i < n; i += 2) {
                        if (v[i-1] < v[i]) {
                            temp = v[i];
                            v[i] = v[i-1];
                            v[i-1] = temp;
                        }
                    }
            } else {
                #pragma omp for
                    for (i = 1; i < n-1; i += 2) {
                        if (v[i] < v[i+1]) {
                            temp = v[i];
                            v[i] = v[i+1];
                            v[i+1] = temp;
                        }
                    }
            }
        }
    }

    display_vector(v);

    return 0;
}
