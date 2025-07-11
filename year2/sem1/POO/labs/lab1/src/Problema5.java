public class Problema5 {
    public int power(int baza, int exp) {
        if (exp == 0)
            return 1;
        return baza * power(baza, exp - 1);
    }

    public void printPower(int baza, int exp) {
        System.out.println(power(baza, exp));
    }

    public static void main(String args[]) {
        Problema5 var = new Problema5();
        var.printPower(5, 3);
        System.out.println(Math.pow(5, 3));
    }
}
