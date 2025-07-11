package p2;

import java.util.LinkedList;
import java.util.Set;

public class LinkedSet extends LinkedList implements Set {
    public boolean add(Object obj) {
        if (this.contains(obj))
            return false;
        super.add(obj);
        return true;
    }

    public void add(int i, Object obj) {
        if (this.contains(obj)) {
        }
        else
            super.add(i, obj);
    }

    public Object set(int i, Object obj) {
        Object old = get(i);
        if (!contains(obj))
            super.set(i, obj);
        return old;
    }
}
