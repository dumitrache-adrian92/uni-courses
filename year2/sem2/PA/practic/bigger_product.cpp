#include <bits/stdc++.h>

using namespace std;

int main()
{
    vector<int> nmb;
    int n;

    cin>>n;

    double curr;
    int res = 1;

    for(int i = 0, x; i < n; i++) {
        cin>>x;
        nmb.push_back(x);
    }

    sort(nmb.begin(), nmb.end(), greater<int>());
    curr = nmb[0];

    int i = 1;
    int j = n - 1;

    while(i <= j)
         if(curr / nmb[j] < 1) {
             curr *= nmb[i];
             i++;
             res++;
         } else {
             curr /= nmb[j];
             j--;
         }

    cout<<res;

    return 0;
}
