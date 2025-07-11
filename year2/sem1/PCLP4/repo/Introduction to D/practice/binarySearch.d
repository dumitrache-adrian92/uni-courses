module PCLP4.Introduction_to_D.practice.binarySearch;

int binarysearch1(int[10] arr, int l, int r, int x)
{
    if (r >= l)
    {
        int mid = l + (r - l) / 2;

        // If element is present at middle
        if (arr[mid] == x)
            return mid;

        // If element is smaller than middle
        if (arr[mid] > x)
            return binarysearch1(arr, l, mid - 1, x);

        // Else element is in right subarray
        return binarysearch1(arr, mid + 1, r, x);
    }

    // When element is not present in array
    return -1;
}

void main()
{
    import std.stdio : writeln;

    int[10] a = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];

    writeln(a.binarysearch1(0, arr.length, 3));
}

