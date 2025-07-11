package p1;

public class Test {
    public static void main(String[] args) {
        Vanilla vanillaChocolateIceCream = new Vanilla(new Chocolate(new BasicIceCream()));

        System.out.println("Ingredients: " + vanillaChocolateIceCream.getDescription());
        System.out.println("Price: " + vanillaChocolateIceCream.getPrice());
    }
}
