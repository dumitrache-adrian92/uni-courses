// Serial matrix multiplication

#include <bits/stdc++.h>
#include <omp.h>

using namespace std;

vector<vector<int>> multiply_serial(vector<vector<int>> &a, vector<vector<int>> &b) {
    int n = a.size();
    vector<vector<int>> c(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            c[i][j] = 0.0;

            for (int k = 0; k < n; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return c;
}

vector<vector<int>> multiply_crcw(vector<vector<int>> &a, vector<vector<int>> &b) {
    int n = a.size();
    vector<vector<int>> c(n, vector<int>(n, 0));

    #pragma omp parallel num_threads(n * n * n)
    {
        long long int thread_id = omp_get_thread_num();
        long long int i = thread_id / (n * n);
        long long int j = (thread_id / n) % n;
        long long int k = thread_id % n;

        #pragma omp atomic
            c[i][j] += a[i][k] * b[k][j];
    }
    return c;
}

vector<vector<vector<int>>> multiply_crew(vector<vector<int>> &a, vector<vector<int>> &b) {
    int n = a.size();
    vector<vector<vector<int>>> c(n, vector<vector<int>>(n, vector<int>(n, 0)));

    #pragma omp parallel num_threads(n * n * n)
    {
        long long int thread_id = omp_get_thread_num();
        long long int i = thread_id / (n * n);
        long long int j = (thread_id / n) % n;
        long long int k = thread_id % n;

        c[i][j][k] = a[i][k] * b[k][j];
        float stop = log2f((float)n);
        long long int power = 1;
        #pragma omp barrier
        for (int m = 0; (float) m < stop; m++) {
            if (k % (2 * power) == 0 && k + power < n) {
                c[i][j][k] += c[i][j][k + power];
            }
            power <<= 1;
            #pragma omp barrier
        }
    }

    return c;
}

int main(int argc, char *argv[]) {
    int n = stoi(argv[1]);
    vector<vector<int>> a(n, vector<int>(n, 1));
    vector<vector<int>> b(n, vector<int>(n, 1));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = i + j + 2;
            b[i][j] = i * j + 2;
        }
    }

    double start = omp_get_wtime();
    vector<vector<int>> correct_result = multiply_serial(a, b);
    double end = omp_get_wtime();
    cout << end - start << endl;

    start = omp_get_wtime();
    vector<vector<int>> result = multiply_crcw(a, b);
    end = omp_get_wtime();
    cout << end - start << endl;

    // check if the result is correct
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (result[i][j] != correct_result[i][j]) {
                cout << "Wrong result" << endl;
                return 1;
            }
        }
    }

    start = omp_get_wtime();
    vector<vector<vector<int>>> result_crew = multiply_crew(a, b);
    end = omp_get_wtime();
    cout << end - start << endl;

    // check if the result is correct
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (result_crew[i][j][0] != correct_result[i][j]) {
                cout << "Wrong result" << endl;
                cout << result_crew[i][j][0] << " " << correct_result[i][j] << endl;
                cout << i << " " << j << endl;
                return 1;
            }
        }
    }

    return 0;
}
