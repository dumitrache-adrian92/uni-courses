package p3;

import java.util.*;

public class SListSet extends LinkedList implements SortedSet{
    Comparator c;
    public SListSet() {
        c = null;
    }

    public SListSet(Comparator c) {
        this.c = c;
    }

    public boolean add(Object o) {
        if (!contains(o)) {
            super.add(0);
            Collections.sort(this, c);
            return true;
        }
        else
            return false;
    }

    public Object first() {
        return get(0);
    }

    public Object last() {
        return get(size() - 1);
    }

    public Comparator comparator() {
        return c;
    }

    public SortedSet subSet(Object from, Object to) {
        SListSet result = new SListSet(c);
        for (int i = indexOf(from); i <= indexOf(to); i++) {
            result.add(get(i));
        }
        return result;
    }

    public SortedSet headSet(Object to) {
        SListSet result = new SListSet(c);
        for (int i = 0; i <= indexOf(to); i++) {
            result.add(get(i));
        }
        return result;
    }

    public SortedSet tailSet(Object from) {
        SListSet result = new SListSet(c);
        for (int i = indexOf(from); i < size(); i++) {
            result.add(get(i));
        }
        return result;
    }
}
