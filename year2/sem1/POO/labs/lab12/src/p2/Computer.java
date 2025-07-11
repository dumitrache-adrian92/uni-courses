package p2;

public class Computer extends Product {
    public Computer(double price, String name) {
        super(price, name);
    }

    public double getPriceReduced() {
        return getPrice() - (10.0/100.0) * getPrice();
    }
}
