package p1;

public class BasicIceCream implements IceCream {
    public BasicIceCream() {
        System.out.println("Adding cone.");
    }

    public String getDescription() {
        return "cone";
    }

    public double getPrice() {
        return 0.5;
    }
}
