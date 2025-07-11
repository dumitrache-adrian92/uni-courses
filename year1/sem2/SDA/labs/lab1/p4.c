#include <stdio.h>

void merge(int *v, int s, int d) {
    int m = (s + d) / 2;
    int i = s;
    int j = m + 1;
    int k = 0;
    int tmp[d];
    while (i <= m && j <= d)
        if (v[i] <= v[j])
            tmp[k++] = v[i++];
        else
            tmp[k++] = v[j++];
    while (i <= m)
        tmp[k++] = v[i++];
    while (j <= d)
        tmp[k++] = v[j++];
    for (i = 0; i < k; i++)
        v[s + i] = tmp[i];
}

void mergeSort(int *v, int s, int d) {
    if (s == d)
        return;
    int m = (s + d) / 2;
    mergeSort(v, s, m);
    mergeSort(v, m + 1, d);
    merge(v, s, d);
}

int pozK(int *v, int n, int k) {
    mergeSort(v, 0, n - 1);
    return v[k];
}

int main() {
    int v[10], n, k;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &v[i]);
    scanf("%d", &k);
    printf("%d\n", pozK(v, n, k));
}