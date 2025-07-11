package p2;

import java.util.Vector;

public class ProductFactory {
    private static ProductFactory instance;

    private ProductFactory() {
    }

    public static ProductFactory getInstance() {
        if (instance == null)
            instance = new ProductFactory();
        return instance;
    }

    public static Product factory(String type, String name, double price) {
        if (type.equals("Book"))
            return new Book(price, name);
        else if (type.equals("Beverage"))
            return new Beverage(price, name);
        else if (type.equals("Computer"))
            return new Computer(price, name);
        else if (type.equals("Food"))
            return new Food(price, name);

        return null;
    }

    public static void main(String[] args) {
        System.out.println(ProductFactory.factory("Book", "Introduction to Algorithms", 2000).getPriceReduced());
        System.out.println(ProductFactory.factory("Beverage", "Coke", 7).getPriceReduced());
        System.out.println(ProductFactory.factory("Computer", "Ryzen cu Nvidia", 1000).getPriceReduced());
        System.out.println(ProductFactory.factory("Food", "Introduction to Algorithms", 2000).getPriceReduced());
    }
}
