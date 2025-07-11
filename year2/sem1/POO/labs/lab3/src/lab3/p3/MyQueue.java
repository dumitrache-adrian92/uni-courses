package lab3.p3;

public class MyQueue {
    MyArray arr;
    int infinit = 9500;
    int first, last, n;

    public MyQueue() {
        arr = new MyArray(infinit);
        first = 0;
        last = -1;
        n = 0;
    }

    public int getSize() {
        return n;
    }

    public void enqueue(int value) {
        n += 1;
        last += 1;
        arr.set(last, value);
    }

    public int dequeue() {
        first += 1;
        n -= 1;
        return arr.get(first - 1);
    }

    public boolean isEmpty() {
        return first > last;
    }

    public String toString() {
        String s = "";
        for (int i = first; i <= last; i++) {
            s = s + arr.get(i) + " ";
        }
        return s;
    }
}
class MyArray {
    private int v[];
    private int size;

    public MyArray() {
        this(100);
    }

    public MyArray(int length) {
        size = 0;
        v = new int[length];
    }

    public int get(int poz) {
        if(poz < size) {
            return v[poz];
        } else {
            return -1;
        }
    }

    public void set(int pos, int value) {
        v[pos] = value;
        size++;
    }

    public int getSize() {
        return size;
    }
}

class a {
    public static void main(String args[]) {
        MyQueue queue = new MyQueue();
        queue.enqueue(7);
        queue.enqueue(8);
        queue.enqueue(10);
        queue.enqueue(-1);
        queue.enqueue(2);
        System.out.println(queue);
        System.out.println(queue.dequeue());
        System.out.println(queue.getSize());
        System.out.println(queue);
        queue.enqueue(9);
        queue.enqueue(queue.dequeue());
        queue.enqueue(11);
        queue.enqueue(22);
        System.out.println(queue);
        while(!queue.isEmpty()) {
            System.out.print(queue.dequeue() + " ");
        }
        System.out.println("");
        System.out.println(queue);
    }
}