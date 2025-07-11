import java.util.Vector;

public class P6 {
    public static void main(String []args) {
        Vector v = new Vector();
        v.add(7.5);
        v.add("lol");
        v.add(true);
        v.add(7);
        v.add((float) 7.5);
        v.add('c');
        Vector count = new Vector();
        Vector types = new Vector();
        types.add("class java.lang.Double");
        types.add("class java.lang.String");
        types.add("class java.lang.Boolean");
        types.add("class java.lang.Integer");
        types.add("class java.lang.Double");
        types.add("class java.lang.Character");

        int a = -1;
        for (int i = 0; i < 6; i++) {
            count.add(0);
        }

        for (int i = 0; i < v.size(); i++) {
            for (int j = 0; j < 6; j++) {
                a = v.get(i).getClass().toString().indexOf(types.get(j).toString());
                if (a != -1)
                    count.set(j, (int) count.get(j) + 1);
            }
        }

        System.out.println(types.toString());
        System.out.println(count.toString());
    }
}
