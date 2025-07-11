#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;

    cin >> n;

    int freq1[27] = {0};

    for (int i = 0; i < n; i++) {
        char x;
        cin >> x;

        if (x == '*')
            freq1[26]++;
        else
            freq1[x - 'a']++;
    }

    int freq2[27] = {0};

    for (int i = 0; i < n; i++) {
        char x;
        cin >> x;

        if (x == '*')
            freq2[26]++;
        else
            freq2[x - 'a']++;
    }

    int effay_pairs = 0;

    for (int i = 0; i < 26; i++) {
        if (freq1[i] > freq2[i]) {
            int extra_pairs_needed = min(freq1[i] - freq2[i], freq2[26]);

            effay_pairs += freq2[i] + extra_pairs_needed;

            freq2[26] -= extra_pairs_needed;
        } else if (freq1[i] < freq2[i]) {
            int extra_pairs_needed = min(freq2[i] - freq1[i], freq1[26]);

            effay_pairs += freq1[i] + extra_pairs_needed;

            freq1[26] -= extra_pairs_needed;
        } else
            effay_pairs += freq1[i];
    }

    effay_pairs += freq1[26];

    cout << effay_pairs;

    return 0;
}