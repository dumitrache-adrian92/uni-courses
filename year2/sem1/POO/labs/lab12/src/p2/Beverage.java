package p2;

public class Beverage extends Product {
    public Beverage(double price, String name) {
        super(price, name);
    }

    public double getPriceReduced() {
        return getPrice() - (5.0/100.0) * getPrice();
    }
}
