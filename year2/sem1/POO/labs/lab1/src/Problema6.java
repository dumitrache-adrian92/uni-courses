public class Problema6 {
    public boolean isPrime(int n) {
        if (n == 0 || n == 1)
            return false;
        for (int i = 2; i <= Math.sqrt(n); i++)
            if (n % i == 0)
                return false;
        return true;
    }

    public static void main(String args[]) {
        int i;
        Problema6 var = new Problema6();
        for (i = 0; i < 20; i++) {
            System.out.println(i + ":" + var.isPrime(i));
        }
    }
}
