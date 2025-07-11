import std.stdio;
import core.memory;
import core.stdc.stdlib;
import core.lifetime;

struct LeStruct
{
    int* field;

    this(int val) @nogc
    {
            writeln("hello le struct");
        field = cast(int *)malloc(int.sizeof);
        *field = val;
    }

    ~this() @nogc
    {
        debug
        {
            free(field);
            writeln("bye bye le struct");
        }
    }
}

class LeClass(T)
{
    T* val;

    this(T* val) @nogc
    {
        debug
        {
            write("hello: ");
            writeln(*(*val).field);
        }

        this.val = val;
    }

    ~this() @nogc
    {
        debug
        {
            writeln("bye bye le class ");
        }
    }
}

void makeMeNoGC() @nogc
{
    LeStruct *mem = cast(LeStruct *)malloc(LeStruct.sizeof);
    auto sObj = emplace!LeStruct(mem, 2);
    // LeClass!(LeStruct) *cObj = cast(LeClass!(LeStruct) *)malloc(LeClass!(LeStruct).sizeof);
    // auto cObjaa = emplace!LeClass(cObj, mem);

    debug
    {
        writeln("All going well");
    }
}

void main()
{
    makeMeNoGC();
}
