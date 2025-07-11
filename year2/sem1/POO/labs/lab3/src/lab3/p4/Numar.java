package lab3.p4;

public class Numar {
    int n;
    //returneaza suma dintre nr (membrul clasei) si a
    public int suma(int a) {
        return n + a;
    }
    //returneaza suma dintre nr, a si b
    public int suma(int a, int b) {
        return suma(a) + b;
    }
    //returneaza suma dintre nr, a, b si c
    public int suma(int a, int b, int c) {
        return suma(a, b) + c;
    }
    //returneaza suma dintre nr, a, b, c si d
    public int suma(int a, int b, int c, int d) {
        return suma(a, b, c) + d;
    }

    public static void main(String[] args) {
        Numar a = new Numar();
        a.n = 10;

        System.out.println(a.suma(10, 10, 10, 10));
    }
}
