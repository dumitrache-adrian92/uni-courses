// C++ program to print all permutations using
// Heap's algorithm
#include <stdio.h>

// Prints the array
void printArr(int a[3], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", a[i]);
	printf("\n");
}

void
swap(int *array, int a, int b)
   {
   int temp = array[a]; /* <- it's a double */
   array[a] = array[b];
   array[b] = temp;
   }


// Generating permutation using Heap Algorithm
void heapPermutation(int a[3], int size, int n)
{
	// if size becomes 1 then prints the obtained
	// permutation
	if (size == 1) {
		printArr(a, n);
		return;
	}

	for (int i = 0; i < size; i++) {
		heapPermutation(a, size - 1, n);

		// if size is odd, swap 0th i.e (first) and
		// (size-1)th i.e (last) element
		if (size % 2 == 1)
			swap(a, 0, size - 1);

		// If size is even, swap ith and
		// (size-1)th i.e (last) element
		else
			swap(a, i, size - 1);
	}
}

// Driver code
int main()
{
	int a[3] = { 1, 2, 3 };
	heapPermutation(a, 3, 3);
	return 0;
}
