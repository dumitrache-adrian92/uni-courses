package task1;

import java.util.*;
import java.util.Map;
import java.util.Objects;

public class ArrayMap<K, V> extends AbstractMap<K, V> {
    public class ArrayMapEntry<K, V> implements Map.Entry<K, V> {
        private K key;
        private V value;

        public ArrayMapEntry(K key, V value) {
            this.key = key;
            this.value = value;
        }

        public K getKey() {
            return key;
        }

        public void setKey(K key) {
            this.key = key;
        }

        public V getValue() {
            return value;
        }

        public V setValue(V value) {
            V ret = value;
            this.value = value;
            return ret;
        }

        public String toString() {
            return key + ": " + value;
        }

        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;
            ArrayMapEntry<?, ?> that = (ArrayMapEntry<?, ?>) o;
            return Objects.equals(key, that.key) && Objects.equals(value, that.value);
        }

        public int hashCode() {
            return Objects.hash(key, value);
        }
    }
    ArrayList<ArrayMapEntry<K, V>> map;

    public ArrayMap() {
        map = new ArrayList<ArrayMapEntry<K, V>>();
    }

    public Set entrySet() {
        return new HashSet<>(map);
    }

    public V put(K keyNew, V valNew) {
        V ret;
        for (ArrayMapEntry entry: map) {
            if (keyNew.equals(entry.getKey())) {
                ret = (V) entry.getValue();
                entry.setValue(valNew);
                return ret;
            }
        }
        map.add(new ArrayMapEntry<K, V>(keyNew, valNew));
        return null;
    }

    public int size() {
        return map.size();
    }
}
