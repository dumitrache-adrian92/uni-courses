package p2;

import java.util.*;

public class ArrayMap<K, V> extends AbstractMap<K, V> {
    private Vector<K> keys;
    private Vector<V> values;
    public ArrayMap() {
        keys = new Vector<K>();
        values = new Vector<V>();
    }

    public String toString() {
        String output = "";

        for (int i = 0; i < keys.size(); i++)
            output += keys.get(i) + ": " + values.get(i) + "\n";

        return output;
    }

    public V put(K key, V val) {
        keys.add(keys.size(), key);
        values.add(values.size(), val);
        return val;
    }

    public V get(Object o) {
        return values.get(keys.indexOf(o));
    }

    public Set<K> keySet() {
        TreeSet<K> output = new TreeSet<K>(keys);

        return output;
    }

    public Collection<V> values() {
        Vector<V> output = new Vector<V>(values);

        return output;
    }

    class ArrayMapEntry<K, V> implements Map.Entry<K, V>{
        private K key;
        private V val;

        public ArrayMapEntry(K key, V val) {
            this.key = key;
            this.val = val;
        }

        public K getKey() {
            return key;
        }

        public V getValue() {
            return val;
        }

        public V setValue(V value) {
            V oldVal = val;

            val = value;

            return oldVal;
        }
    }

    public Set<Map.Entry<K, V>> entrySet() {
        HashSet<Map.Entry<K, V>> output = new HashSet<Map.Entry<K, V>>();

        for (int i = 0; i < keys.size(); i++) {
            output.add(new ArrayMapEntry<K, V>(keys.get(i), values.get(i)));
        }

        return output;
    }

    public static void main(String[] args) {
        ArrayMap test = new ArrayMap();

        test.put("da", "nu");
        test.put("alba", "neagra");
        test.put("5", "10");

        System.out.println(test);

        Iterator<Map.Entry<String, String>> itr = test.entrySet().iterator();

        while(itr.hasNext()) {
            System.out.println(itr.next().getKey());
        }
    }
}
