#include <bits/stdc++.h>

using namespace std;

int main()
{
    vector<int> important;
    int battery_life = 0;
    int n;

    cin >> n;

    for (int i = 0, imp, dur; i < n; i++) {
        cin >> imp >> dur;

        if (imp == 0)
            battery_life += dur;
        else
            important.push_back(dur);
    }

    size_t can_miss;

    cin >> can_miss;

    sort(important.begin(), important.end(), greater<int>());

    for (size_t i = 0; i < min(can_miss, important.size()); i++) {
        battery_life += important[i];
    }

    for (size_t i = can_miss; i < important.size(); i++) {
        battery_life -= important[i];
    }

    cout << battery_life << endl;

    return 0;
}