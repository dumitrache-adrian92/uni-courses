package p2;

public class MyStack {
    Array arr;

    public MyStack() {
        arr = new Array();
    }

    public void push(Integer x) {
        arr.addElement(x);
    }

    public Integer pop() {
        Integer result = arr.get(arr.getSize() - 1);

        arr.remove(arr.getSize() - 1);

        return result;
    }
}
