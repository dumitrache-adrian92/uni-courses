package p3;

import java.util.ArrayList;

public class IntegerMatrix extends AMatrix<Integer> {
    public String toString() {
        String out = "";

        for (ArrayList i: this)
            out += i.toString() + "\n";

        return out;
    }

    public AMatrix<Integer> addition(AMatrix<Integer> m1) {
        for (ArrayList<Integer> i: this) {
            for (int j = 0; j < i.size(); j++) {
                i.set(j, sum(i.get(j), m1.get(indexOf(i)).get(j)));
            }
        }

        return this;
    }

    public Integer sum(Integer obj1, Integer obj2) {
        return Integer.sum(obj1, obj2);
    }

    public static void main(String[] args) {
        IntegerMatrix a = new IntegerMatrix();
        ArrayList l = new ArrayList();
        l.add(1);
        l.add(2);
        l.add(3);
        l.add(4);
        ArrayList l2 = new ArrayList(l);
        a.add(l);
        a.add(l2);

        System.out.println(a.addition(a));
    }
}
