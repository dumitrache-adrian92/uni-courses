import std.algorithm.mutation: reverse;
import std.stdio;
// TODO: Change the function's signature


T[] checkNumbers(T)(T[] arr)
{
    T[] result = [];
    static if (is(T == double) || is(T == int)) {
        for (int i = 0; i < arr.length; i++) {
            T max = 1;

            while (max <= arr[i])
                max *= 2;

            result ~= [max];
        }

        //writeln(result);
        return result;

    }
    else
        return arr.reverse;
}

unittest
{
    int[] arr1 = [10, 20, 30, 40, 64];
    double[] arr2 = [1.0, 2.0, 3.0, 4.0, 5.0];
    string[] arr3 = ["PCLP4", "SO", "IOCLA"];

    assert(checkNumbers(arr1) == [16, 32, 32, 64, 128]);
    assert(checkNumbers(arr2) == [2.0, 4.0, 4.0, 8.0, 8.0]);
    assert(checkNumbers(arr3) == ["IOCLA", "SO", "PCLP4"]);
}
