import java.util.Arrays;

public class Problema8 {
    public static void main(String args[]) {
        int arr[]= {1, 6, 78, 5, 4, 6, 8578, 4};
        int n = 8, i;
        Arrays.sort(arr);
        for (i = 0; i < n; i++)
            System.out.print(arr[i] + " ");

        System.out.println(Arrays.binarySearch(arr, 4));
    }
}
