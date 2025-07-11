package task3;

import java.util.Iterator;
import java.util.ListIterator;

public class LinkedList<T> implements Iterable{
    private static class Node<T> {
        T value;
        Node<T> next;

        public Node(T value) {
            this.value = value;
            next = null;
        }

        public Node(T value, Node next) {
            this.value = value;
            this.next = next;
        }
    }

    private class ListIterator implements Iterator {
        Node current;

        public ListIterator(LinkedList list) {
            current = list.first;
        }

        public boolean hasNext() {
            if (current != null)
                return true;
            return false;
        }

        public Object next() {
            Node result = current;
            current = current.next;
            return result.value;
        }
    }

    Node first, last;

    public LinkedList() {
        first = null;
        last = null;
    }

    public void addFirst(T data) {
        Node n = new Node(data, first);
        first = n;
        if (last == null)
            last = first;
    }

    public void add(T data) {
        if (last == null) {
            addFirst(data);
            return;
        }

        Node n = new Node(data);
        last.next = n;
        last = n;
    }

    public Iterator<T> iterator() {
        return new LinkedList<T>.ListIterator(this);
    }
}
