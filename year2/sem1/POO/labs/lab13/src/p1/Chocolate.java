package p1;

public class Chocolate extends ToppingDecorator {
    public Chocolate(IceCream decoratedIceCream) {
        super(decoratedIceCream);
        System.out.println("Adding chocolate.");
    }

    public double getPrice() {
        return super.getPrice() + 1.5;
    }

    public String getDescription() {
        return super.getDescription() + ", chocolate";
    }
}
