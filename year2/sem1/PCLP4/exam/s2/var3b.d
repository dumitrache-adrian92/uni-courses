import std.stdio;
import std.range;
import std.traits;
import std.typecons;
import std.algorithm;

struct MyStruct {
    int[] elems;

    auto filter(alias pred)()
    {
        return elems.filter!pred;
    }

    bool empty()
    {
        return elems.length == 0;
    }

    int front()
    {
        return elems[0];
    }

    void popFront()
    {
        elems = elems[1 .. $];
    }
}

auto myFilter(alias pred, Range)(Range range)
{
    if (range.filter!pred())
    {
        // If the user supplied type already defins `filter`, we should use it
        return range.filter!pred();
    }
    else
    {
        // Filter the range using the range interface and append the valid elements to a new result
        // For this exercise, you are **NOT** allowed to use library implementation of `filter`
        ElementType!(Range)[] res;
        return res;
    }
}

struct MyPair {
    int[2] pair;
}

void main(string[] args)
{
    int[] intHaystack = [1, 2, 3, 4, 5, 6, 7, 8];

    assert(equal(intHaystack.myFilter!(a => a < 5), [1, 2, 3, 4]));
    assert(equal(intHaystack.myFilter!(a => a > 5), [6, 7, 8]));
    assert(intHaystack.myFilter!(a => a > 42).empty);

    MyStruct structHaystack = MyStruct([1, 2, 3, 4, 5, 6, 7, 8]);
    assert(equal(structHaystack.myFilter!(a => a < 6), [1, 2, 3, 4, 5]));
    assert(equal(structHaystack.myFilter!(a => a > 6), [7, 8]));
    assert(structHaystack.myFilter!(a => a > 42).empty);

    //// Those are not input ranges, so the compiler should error here, rather than in the template
    MyPair pair = MyPair([10, 20]);
    auto r = pair.myFilter!(a => a < 20);

    auto tpl = tuple(1, 2, 3, 4);
    tpl.myFilter!(a => a < 20);
}
