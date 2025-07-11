public class Problema7 {

    public static boolean prime(int n) {
        for (int i = 2; i <= Math.sqrt(n); i++)
            if (n % i == 0)
                return false;
        return true;
    }
    public static void goldbach(int x) {
        int i, j;
        for (i = 1; i < x; i++)
            for (j = 1; i + j <= x; j++) {
                if (i + j == x && prime(i) == true && prime(j) == true) {
                    System.out.println(x + " = " + i + " + " + j);
                }
            }
    }

    public static void main(String args[]) {
        int i;
        for (i = 0; i < 100; i += 2) {
            goldbach(i);
        }
    }
}
