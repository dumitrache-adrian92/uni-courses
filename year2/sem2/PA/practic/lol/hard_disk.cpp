#include <bits/stdc++.h>

using namespace std;

int main()
{
    int d, n;

    cin >> d >> n;

    vector<int> to_read;

    for (int i = 0, x; i < n; i++) {
        cin >> x;
        to_read.push_back(x);
    }

    sort(to_read.begin(), to_read.end());

    int min_operations = 0;

    if (n != 0)
        min_operations = to_read[n - 1] - to_read[0];

    for (int i = 0; i < n; i++) {
        int forward;

        if (i == 0)
            forward = to_read[n - 1] - to_read[i];
        else
            forward = (d - 1 - to_read[i]) + to_read[(i + n - 1) % n] + 1;

        int backwards;

        if (i == n - 1)
            backwards = to_read[i] - to_read[0];
        else
            backwards = to_read[i] + 1 + (d - 1 - to_read[(i + n + 1) % n]);

        min_operations = min(min_operations, min(forward, backwards));
    }

    cout << min_operations;

    return 0;
}