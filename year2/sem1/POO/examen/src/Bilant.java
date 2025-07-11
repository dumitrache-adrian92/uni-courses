import org.w3c.dom.stylesheets.LinkStyle;

import java.util.ArrayList;
import java.util.List;
import java.util.Vector;

public class Bilant implements Comparable<Bilant>{
    int pozitive, negative;

    public Bilant() {
        this(0, 0);
    }

    public Bilant(int pozitive, int negative) {
        this.pozitive = pozitive;
        this.negative = negative;
    }

    public String toString() {
        return pozitive + " " + negative;
    }

    public int compareTo(Bilant o) {
        int thisDiff = pozitive - negative;
        int oDiff = o.pozitive - o.negative;

        return oDiff - thisDiff;
    }

    ArrayList<Integer> go() {
        List<Integer> l = new ArrayList<>();

        return (ArrayList<Integer>) l;
    }

    public static void main(String[] args) {
        Vector<Bilant> v = new Vector<>();
        v.add(new Bilant());
        v.add(new Bilant(1, -5));
        v.add(new Bilant(7, 3));

        v.sort(null);

        System.out.println(v);
    }
}
