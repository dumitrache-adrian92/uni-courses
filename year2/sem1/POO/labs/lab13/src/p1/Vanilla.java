package p1;

public class Vanilla extends ToppingDecorator {
    public Vanilla(IceCream decoratedIceCream) {
        super(decoratedIceCream);
        System.out.println("Adding vanilla.");
    }

    public double getPrice() {
        return super.getPrice() + 2.0;
    }

    public String getDescription() {
        return super.getDescription() + ", vanilla";
    }
}
