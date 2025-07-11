#include <bits/stdc++.h>

using namespace std;

/*
 * secventa de elemente cu suma maxima in care niciun element nu este vecin cu
 * alt element din vector
 */

unsigned int max_calc(vector<unsigned int> subsequence, vector<unsigned int> v) {
    unsigned int sum = 0;
    for (const auto i : subsequence)
        sum += v[i];
    return sum;
}

vector<unsigned int> max_sequence(vector<unsigned int> v, vector<unsigned int> subsequence, unsigned int i)
{
    if (i == v.size())
        return subsequence;

    vector<unsigned int> n1;
    vector<unsigned int> n2;

    copy(subsequence.begin(), subsequence.end(), back_inserter(n1));
    copy(subsequence.begin(), subsequence.end(), back_inserter(n2));

    if (!n1.empty() && n1.back() == i - 1)
        return max_sequence(v, subsequence, i + 1);
    else {
        n1.push_back(i);

        vector<unsigned int> r1 = max_sequence(v, n1, i + 1);
        vector<unsigned int> r2 = max_sequence(v, n2, i + 1);

        if (max_calc(r1, v) > max_calc(r2, v))
            return r1;
        else
            return r2;
    }
}

int main()
{
    vector<unsigned int> v;
    vector<unsigned int> s;

    v.push_back(5);
    v.push_back(5);
    v.push_back(100);
    v.push_back(10);
    v.push_back(10);

    vector<unsigned int> r = max_sequence(v, s, 0);

    for (const auto i : r)
        cout<<v[i]<<" ";
    cout<<endl;
}