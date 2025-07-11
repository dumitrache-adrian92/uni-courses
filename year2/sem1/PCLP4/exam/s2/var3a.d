import std.stdio;
import std.algorithm;
import std.array;
import std.math.exponential;

void main(string[] args)
{
    auto values = [
        [63, 72, 75, 51, 83],
        [44, 53, 57, 56, 48],
        [71, 77, 82, 91, 76],
        [67, 56, 82, 33, 74],
        [64, 76, 72, 63, 76],
        [47, 56, 49, 53, 42],
        [91, 93, 90, 88, 96],
        [61, 56, 77, 74, 74],
    ];

    auto minElems = values.map!(minElement).map!("a * a");

    assert(equal(minElems, [2601, 1936, 5041, 1089, 3969, 1764, 7744, 3136]));

    auto uniqValues = values.join.sort.uniq;
    assert(equal(uniqValues, [33, 42, 44, 47, 48, 49, 51, 53, 56, 57, 61, 63, 64, 67, 71, 72, 74, 75, 76, 77, 82, 83, 88, 90, 91, 93, 96]));
}
