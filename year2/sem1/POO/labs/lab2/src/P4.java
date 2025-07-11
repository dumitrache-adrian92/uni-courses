import java.util.Vector;
import java.util.Random;

public class P4 {
    public static Vector intersection(Vector v1, Vector v2) {
        Vector result = new Vector(20);
        for (Object x : v1)
            if (v2.contains(x) && result.contains(x) != true)
                result.add(x);
        return result;
    }

    public static Vector difference(Vector v1, Vector v2) {
        Vector result = new Vector(20);
        for (Object x : v1)
            if (v2.contains(x) != true && result.contains(x) != true)
                result.add(x);
        return result;
    }

    public static Vector reunion(Vector v1, Vector v2) {
        Vector result = new Vector(20);
        for (Object x : v1)
            result.add(x);
        for (Object x : v2)
            result.add(x);
        return result;
    }

    public static void main(String []args) {
        Vector v1 = new Vector(10);
        Vector v2 = new Vector(10);
        Random rn = new Random();

        for (int i = 0; i < 10; i++) {

            v1.add(rn.nextInt(21));
            v2.add(rn.nextInt(21));
        }

        System.out.println(v1);
        System.out.println(v2);

        Vector v3 = intersection(v1, v2);
        System.out.println(v3);

        v3 = difference(v1, v2);
        System.out.println(v3);

        v3 = reunion(v1, v2);
        System.out.println(v3);
    }
}
