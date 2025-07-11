#include <bits/stdc++.h>

using namespace std;

vector<int> x;
int n;

void Afis()
{
    for (int j = 1; j <= n; j++)
        cout << x[j] << " ";
    cout << endl;
}

bool OK(int k)
{
    for (int i = 1; i < k; ++i)
        if (x[k] == x[i] || (x[i] & 1) == (x[i + 1] & 1))
            return false;

    return true;
}

bool Solutie(int k)
{
    for (int i = 1; i < k; i++)
        if ((x[i] & 1) == (x[i + 1] & 1))
            return false;

    return k == n;
}

void back(int k)
{
    for (int i = 1; i <= n; ++i)
    {
        x[k] = i;
        if (OK(k)) {
            if (Solutie(k))
                Afis();
            else
                back(k + 1);
        }
    }
}

int main()
{
    cin >> n;

    x.resize(n + 1);

    if (n == 0)
        cout << -1;
    else
        back(1);

    return 0;
}