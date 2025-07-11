import java.util.StringTokenizer;

public class P2 {
    public static void main(String args[]) {
        String s1 = "sir2";
        String s = "sir1 si sir2 sunt 2 siruri";
        String a[] = s.split(" ");
        int count = 0;
        for (int i = 0; i < a.length; i++)
            if (a[i].equals((s1)))
                count++;
        System.out.println(count);
        count = 0;
        StringTokenizer b = new StringTokenizer(s);
        while (b.hasMoreTokens())
            if (b.nextToken().equals(s1))
                count++;
        System.out.println(count);
    }
}
