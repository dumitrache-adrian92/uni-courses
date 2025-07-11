package p2;

public class Food extends Product {
    public Food(double price, String name) {
        super(price, name);
    }

    public double getPriceReduced() {
        return getPrice() - (20.0 / 100.0) * getPrice();
    }
}
