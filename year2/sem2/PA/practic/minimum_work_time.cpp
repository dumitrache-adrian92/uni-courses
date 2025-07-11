#include <bits/stdc++.h>
using namespace std;

const int NMAX = 120000;
long long a[NMAX + 1];
int n, k;

bool check(long long sum)
{
    int cnt = 0;
    long long s = 0;

    for (int i = 1; i <= n; i++) {
        if(a[i] > sum)
            return false;

        if(s + a[i] <= sum) {
            s += a[i];
        } else {
            cnt++;
            s = a[i];
        }
    }

    if (sum > 0) {
        cnt++;
    }

    return cnt <= k;
}

int main()
{
    cin >> n >> k;
    long long sum = 0;
    long long mx = 0;

    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
        mx = max(mx, a[i]);
    }

    sort(a + 1, a + n + 1);

    long long st = mx;
    long long dr = sum;
    long long sol = 0;

    while(st <= dr) {
        long long mid = (st + dr) / 2;

        if(check(mid)) {
            sol = mid;
            dr = mid - 1;
        } else {
            st = mid + 1;
        }
    }

    cout << sol;

    return 0;
}