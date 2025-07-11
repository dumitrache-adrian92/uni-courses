#include <stdio.h>

void sumAndProduct(int *v, int s, int d, int *sum, int *prod) {
    if(s==d){
        *sum += v[s];
        *prod *= v[d];
        return;
    }
    int m = (s+d)/2;
    sumAndProduct(v, s, m, sum, prod);
    sumAndProduct(v, m+1, d, sum, prod);
    return;
}

int main() {
    int v[10], n;
    scanf("%d", &n);
    for (int i=0; i<n; i++)
        scanf("%d", &v[i]);
    int sum, prod;
    sum = 0;
    prod = 1;
    sumAndProduct(v, 0, n-1, &sum, &prod);
    printf("%d %d\n", sum, prod);
}