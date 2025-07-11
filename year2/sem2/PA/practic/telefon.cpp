#include <bits/stdc++.h>

using namespace std;

// doesnt work fmm
int main()
{
    int n, x;

    cin >> n >> x;

    vector<int> v;

    for (int i = 0, a; i < n; i++) {
        cin >> a;
        v.push_back(a);
    }

    uint64_t money_spent = 0;

    for (int i = 0; i < n; i++) {
        int spent_if_better_charging_or_end = 0;
        int j;
        int mini = v[i + 1];
        int idx = i + 1;

        for (j = i + 1; j < n && v[j] > v[i] && j - i <= x; j++) {
            spent_if_better_charging_or_end += v[i];

            if (mini > v[j]) {
                mini = v[j];
                idx = j;
            }
        }

        if (j - i == x + 1) {
            money_spent += (idx - i) * v[i];
            i = idx;
        } else {
            money_spent += spent_if_better_charging_or_end;
            i = j;
        }
    }

    cout << money_spent;

    return 0;
}