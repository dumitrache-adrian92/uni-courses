package lab3.p2;

public class Produs {
    String name;
    double price;
    int quantity;

    public Produs(String nume, double pret, int cantitate) {
        name = nume;
        price = pret;
        quantity = cantitate;
    }

    public String toString() {
        return "Produs" + " " + name + " " + price + " " + quantity;
    }

    public double getTotalProdus() {
        return price * quantity;
    }
}
