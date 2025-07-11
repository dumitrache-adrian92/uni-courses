#include <bits/stdc++.h>

using namespace std;

int64_t SolveTask1(vector<int> a, vector<int> b) {
    vector<int> merged(2 * a.size());

    // sort the two vectors
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    // merge them
    merge(a.begin(), a.end(), b.begin(), b.end(), merged.begin());

    int64_t sum = 0;

    // the result is the sum of the second half
    for (size_t i = a.size(); i < 2 * a.size(); i++)
        sum += merged[i];

    return sum;
}

int64_t SolveTask2(vector<int> a, vector<int> b, int moves) {
    uint32_t i;
    int64_t score = 0;

    // make it so all the maximums of each pair are in a for simplicity
    for (i = 0; i < a.size(); i++)
        if (a[i] < b[i])
            swap(a[i], b[i]);

    // sort a ascendingly and b descendingly
    sort(a.begin(), a.end());
    sort(b.begin(), b.end(), greater<int>());

    i = 0;

    while (moves != 0)
        /* if it results in a better score, swap the greatest value in b with
           the smallest in a, otherwise stop even if we haven't reached the
           allowed number of moves */
        if (a[i] < b[i]) {
            swap(a[i], b[i]);
            i++;
            moves--;
        } else {
            break;
        }

    // calculate the score
    for (i = 0; i < a.size(); i++)
        score += a[i];

    return score;
}

vector<int> ReadVector(istream& is, int size) {
    vector<int> vec(size);
    for (auto& num : vec) {
        is >> num;
    }
    return vec;
}

int main() {
    ifstream fin("nostory.in");
    ofstream fout("nostory.out");

    int task;
    fin >> task;

    int n, moves;
    if (task == 1) {
        fin >> n;
    } else {
        fin >> n >> moves;
    }

    auto a = ReadVector(fin, n);
    auto b = ReadVector(fin, n);

    auto res = task == 1 ? SolveTask1(a, b) : SolveTask2(a, b, moves);
    fout << res << "\n";

    return 0;
}
