package p2;

public class Book extends Product{
    public Book(double price, String name) {
        super(price, name);
    }

    public double getPriceReduced() {
        return getPrice() - (15.0/100.0) * getPrice();
    }
}
