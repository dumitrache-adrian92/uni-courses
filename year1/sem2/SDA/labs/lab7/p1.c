#include <stdio.h>
#include <stdlib.h>

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
    int largest = i; // Initialize largest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // If largest is not root
    if (largest != i) {
        swap(&arr[i], &arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

void filtrareInJos(int *maxHeap, int *n) {
    maxHeap[0] = maxHeap[*n - 1];
    *n -=1;
    heapify(maxHeap, *n, 0);
}

int main() {
    int maxHeap[1000], n, i;
    n = 0;
    filtrareInSus(maxHeap, &n, 10);
    filtrareInSus(maxHeap, &n, 20);
    filtrareInSus(maxHeap, &n, 30);
    filtrareInSus(maxHeap, &n, 40);
    filtrareInSus(maxHeap, &n, 50);
    filtrareInSus(maxHeap, &n, 60);
    filtrareInJos(maxHeap, &n);
    filtrareInJos(maxHeap, &n);

    for (i = 0; i < n; i++)
        printf("%d ", maxHeap[i]);
    printf("\n");

    return 0;
}