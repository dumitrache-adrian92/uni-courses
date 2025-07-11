package lab3.p2;

public class Magazin {
    String name;
    Produs p1, p2, p3;

    public Magazin(String nume, Produs x, Produs y, Produs z) {
        name = nume;
        p1 = x;
        p2 = y;
        p3 = z;
    }

    public String toString() {
        return p1.toString() + "\n" + p2.toString() + "\n" + p3.toString();
    }

    public double getTotalMagazin() {
        return p1.getTotalProdus() + p2.getTotalProdus() + p3.getTotalProdus();
    }

    public static void main(String[] args) {
        Magazin john = new Magazin("Complex Comercial John Gavana",
                                    new Produs("ceas", 20, 100),
                                    new Produs("curea", 66, 1000),
                                    new Produs("tricou tommy", 10, 5));

        System.out.println(john.getTotalMagazin());
        System.out.println(john.toString());
    }
}
