import std.stdio;

int[string] mergeAAs(int[string] a, int[string] b)
{
    int[string] result;

    foreach (key, value; b)
    {
        result[key] = value;
    }

    foreach (key, value; a)
    {
        int ok = 1;
        foreach (key2, value2; b)
            if (key == key2)
                ok = 0;

        if (ok == 1)
            result[key] = value;
    }
    return result;
}

unittest
{
    int[string] a = ["a": 1, "b": 2];
    int[string] b = ["c": 3, "d": 4];
    assert(mergeAAs(a, b) == ["a": 1, "b": 2, "c": 3, "d": 4]);

    int[string] c = ["ab": 1, "cd": 2];
    int[string] d = ["cd": 3, "xy": 4];
    assert(mergeAAs(c, d) == ["ab": 1, "cd": 3, "xy": 4]);
}
