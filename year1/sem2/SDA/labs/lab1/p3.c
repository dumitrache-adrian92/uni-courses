#include <stdio.h>

int binarySearchR(int *v, int s, int d, int x) {
    int m = (s+d)/2;
    if (s>d)
        return -1;
    if(v[m] == x)
        return m;
    else if (v[m]<x)
        binarySearchR(v, m+1, d, x);
    else
        binarySearchR(v, s, m-1, x);

}

int main() {
    int v[10], n, x;
    scanf("%d", &n);
    for (int i=0; i<n; i++)
        scanf("%d", &v[i]);
    scanf("%d", &x);
    printf("%d\n", binarySearchR(v, 0, n-1, x));
}