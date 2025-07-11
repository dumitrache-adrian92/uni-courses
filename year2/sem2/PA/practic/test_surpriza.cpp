#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, k;

    cin >> n >> k;

    vector<int> problems(n);

    for (int i = 0; i < n; i++)
        cin >> problems[i];

    sort(problems.begin(), problems.end());

    int min_index = 0;
    int min_dif = problems[k - 1] - problems[0];

    for (int i = 1; i < n - k; i++)
        if (min_dif > problems[i + k - 1] - problems[i]) {
            min_index = i;
            min_dif = problems[i + k - 1] - problems[i];
        }

    cout << min_dif << '\n';

    for (int i = min_index; i <= min_index + k - 1; i++)
        cout << problems[i] << " ";
}