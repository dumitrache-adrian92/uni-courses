#include <stdio.h>
#include <stdlib.h>

struct hNod {
    char item;
    int freq;
    struct hNod *left, *right;
};

struct MinHeap {
    int size;
    int capacity;
    struct hNod **array;
};

struct hNod *newNode(char item, int freq) {
    struct hNod *temp = (struct hNod *)malloc(sizeof(struct hNod));

    temp->left = temp->right = NULL;
    temp->item = item;
    temp->freq = freq;

    return temp;
}

struct MinHeap *createMinH(int capacity) {
    struct MinHeap *minHeap = (struct MinHeap *)malloc(sizeof(struct MinHeap));

    minHeap->size = 0;

    minHeap->capacity = capacity;

    minHeap->array = (struct hNod **)malloc(minHeap->capacity * sizeof(struct hNod *));
    return minHeap;
}

void swaphNod(struct hNod **a, struct hNod **b) {
    struct hNod *t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap *minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swaphNod(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

int checkSizeOne(struct MinHeap *minHeap) {
    return (minHeap->size == 1);
}

struct hNod *extractMin(struct MinHeap *minHeap) {
    struct hNod *temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];

    --minHeap->size;
    minHeapify(minHeap, 0);

    return temp;
}

void insertMinHeap(struct MinHeap *minHeap, struct hNod *minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

void buildMinHeap(struct MinHeap *minHeap) {
    int n = minHeap->size - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

int isLeaf(struct hNod *root) {
    return !(root->left) && !(root->right);
}

struct MinHeap *createAndBuildMinHeap(char item[], int freq[], int size) {
    struct MinHeap *minHeap = createMinH(size);

    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(item[i], freq[i]);

    minHeap->size = size;
    buildMinHeap(minHeap);

    return minHeap;
}

struct hNod *buildHuffmanTree(char item[], int freq[], int size) {
    struct hNod *left, *right, *top;
    struct MinHeap *minHeap = createAndBuildMinHeap(item, freq, size);

    while (!checkSizeOne(minHeap)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        top = newNode('$', left->freq + right->freq);

        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}

void printHCodes(struct hNod *root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        printHCodes(root->left, arr, top + 1);
    }
    if (root->right) {
        arr[top] = 1;
        printHCodes(root->right, arr, top + 1);
    }
    if (isLeaf(root)) {
        printf("  %c   | ", root->item);
        printArray(arr, top);
    }
}

void HuffmanCodes(char item[], int freq[], int size) {
    struct hNod *root = buildHuffmanTree(item, freq, size);

    int arr[1000], top = 0;

    printHCodes(root, arr, top);
}

void printArray(int arr[], int n) {
    int i;
    for (i = 0; i < n; ++i)
        printf("%d", arr[i]);

    printf("\n");
}

int main() {
    char arr[] = {'A', 'B', 'C', 'D'};
    int freq[] = {5, 1, 6, 3};

    int size = sizeof(arr) / sizeof(arr[0]);

    printf(" Char | Huffman code ");
    printf("\n--------------------\n");

    HuffmanCodes(arr, freq, size);
}