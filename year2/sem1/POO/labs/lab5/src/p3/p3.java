package p3;

import java.util.Collections;
import java.util.Scanner;
import java.util.Vector;

class NumarNegativ extends Exception {
    public NumarNegativ() {
        super("Numarul introdus este negativ!");
    }
}

public class p3 {
    Vector v = new Vector();

    public void myRead() throws NumarNegativ{
        Scanner s = new Scanner(System.in);
        int x = s.nextInt();
        while (x > 0) {
            v.add(x);
            x = s.nextInt();
        }
        throw new NumarNegativ();
    }

    public int max() {
        return (int) Collections.max(v);
    }

    public static void main(String[] args) {
        p3 test = new p3();
        try {
            test.myRead();
        } catch (NumarNegativ n) {
            System.out.println("Nr. negativ prins.");
        }
        System.out.println(test.v);
        System.out.println(test.max());
    }
}
