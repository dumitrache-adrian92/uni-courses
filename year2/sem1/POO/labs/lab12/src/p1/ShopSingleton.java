package p1;

import java.util.Vector;

public class ShopSingleton {
    private Vector<Product> products;
    private String name;
    private static ShopSingleton instance;

    private ShopSingleton() {
        name = "null";
        products = new Vector<Product>();
    }

    private ShopSingleton(String name) {
        this.name = name;
        products = new Vector<Product>();
    }

    public static ShopSingleton getInstance() {
        if (instance == null)
            instance = new ShopSingleton();
        return instance;
    }

    public static ShopSingleton getInstance(String name) {
        if (instance == null)
            instance = new ShopSingleton(name);
        return instance;
    }

    public void showProducts(){
        System.out.println(products);
    }

    public void addProduct(Product x) {
        products.add(x);
    }

    public void removeProduct(Product x) {
        products.remove(x);
    }

    public Product getCheapestProduct() {
        Product result = products.get(0);
        for (Product p: products)
            if (p.getPrice() < result.getPrice())
                result = p;

        return result;
    }

    public static void main(String[] args) {
        ShopSingleton.getInstance().addProduct(new Product(100, "Lapte"));
        ShopSingleton.getInstance().addProduct(new Product(50, "Tigari"));
        Product test = new Product(1000, "ceva");
        ShopSingleton.getInstance().addProduct(test);

        ShopSingleton.getInstance().showProducts();

        ShopSingleton.getInstance().removeProduct(test);
        ShopSingleton.getInstance().showProducts();

        System.out.println(ShopSingleton.getInstance().getCheapestProduct());
    }
}
