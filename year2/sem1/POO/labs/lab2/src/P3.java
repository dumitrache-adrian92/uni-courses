import java.util.Vector;
import java.util.Random;
import java.util.Collections;

public class P3 {
    public static int deleteValue(Vector v, int x) {
        int result = v.size();
        while (v.removeElement(x));
        result -= v.size();
        return result;
    }

    public static void main(String args[]) {
        Vector v = new Vector(20);
        Random rn = new Random();

        for (int i = 0; i < 20; i++)
            v.add(rn.nextInt(10 - 0 + 1) + 0);

        System.out.println(deleteValue(v, 4));
        System.out.println(v.toString());

        int max = (int) Collections.max(v), min = (int) Collections.min(v);
        int mean = 0;
        for (int i = 0; i < v.size(); i++)
            mean += (int) v.get(i);

        mean /= v.size();

        System.out.println(max);
        System.out.println(v.indexOf(min));
        System.out.println(mean);
    }
}
