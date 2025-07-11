package p3;

import java.util.Hashtable;

public class HSet extends Hashtable {
    public boolean add(Object val) {
        if (containsKey(val))
            return false;
        put(val, val);
        return true;
    }

    public String toString() {
        String s = "";
        for (Object key:keySet()) {
            s += key.toString() + " ";
        }
        return s;
    }

    public Object remove(Object key) {
        Object result = super.get(key);
        super.remove(key);
        return result;
    }
}
