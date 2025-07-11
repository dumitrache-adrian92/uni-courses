#include <stdio.h>

int max(int a, int b) {
    if (a>b)
        return a;
    else return b;
}

int maxim(int *v, int s, int d) {
    if (s==d)
        return v[s];
    int m = (s + d) / 2;
    int a, b;
    a = maxim(v, s, m);
    b = maxim(v, m+1, d);
    return max(a, b);
}

int main() {
    int v[10], n;
    scanf("%d", &n);
    for (int i=0; i<n; i++)
        scanf("%d", &v[i]);
    printf("%d\n", maxim(v, 0, n-1));
}