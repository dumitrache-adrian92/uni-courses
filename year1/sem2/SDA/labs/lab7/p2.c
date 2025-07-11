#include <stdio.h>

void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void filtrareInSus(int *maxHeap, int *n, int new) {
    maxHeap[*n] = new;
    int i = *n;
    while ((i - 1) / 2 >= 0 && maxHeap[i] > maxHeap[(i - 1) / 2]) {
        swap(&maxHeap[i], &maxHeap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
    *n +=1;
}

void heapify(int arr[], int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);

        heapify(arr, n, largest);
    }
}

void filtrareInJos(int *maxHeap, int *n) {
    maxHeap[0] = maxHeap[*n - 1];
    *n -=1;
    heapify(maxHeap, *n, 0);
}

int main() {
    int arr[10] = {3, 5, 2, 5, 4, 7};
    int maxHeap[10], n = 0, i;
    for (i = 0; i < 6; i++)
        filtrareInSus(maxHeap, &n, arr[i]);
    for (i = 5; i >= 0; i--) {
        arr[i] = maxHeap[0];
        filtrareInJos(maxHeap, &n);
    }
    for (int i = 0; i < 6; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}