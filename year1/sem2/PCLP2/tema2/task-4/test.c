#include <stdio.h>
void printSpiral(int arr[5][5], int N) {
    int i, j, k;
    for (i = N - 1, j = 0; i > 0; i--, j++) {
        //print top row
        for (k = j; k < i; k++)
            printf("%d %d\n", j, k);
        /*// print last column
        for (k = j; k < i; k++)
            printf("%d %d\n", k, i);
        // print last row
        for (k = i; k > j; k--)
            printf("%d %d\n", i, k);
        // print first column
        for (k = i; k > j; k--)
            printf("%d %d\n", k, j);
    */}
    // if odd size matrix print the middle value
    int middle = (N - 1) / 2;
    if (N % 2 == 1)
        printf("%d", arr[middle][middle]);
}

int main() {
    int i, j;
    int arr1[5][5] = {{1, 2, 3, 4, 5},
                      {6, 7, 8, 9, 10},
                      {11, 12, 13, 14, 15},
                      {16, 17, 18, 19, 20},
                      {21, 22, 23, 24, 25}};
    printSpiral(arr1, 5);
    return 0;
}