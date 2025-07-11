#include <stdio.h>

void heapify(int arr[], int n, int i) {
    int temp;
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        {
            temp = arr[i];
            arr[i] = arr[largest];
            arr[largest] = temp;
        }

        heapify(arr, n, largest);
    }
}

void buildHeap(int arr[], int n) {
    int i;
    for (i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
}

int main() {
    int n = 6;
    int v[6] = {1, 2, 3, 4, 5, 6};
    buildHeap(v, n);
    for (int i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");
}