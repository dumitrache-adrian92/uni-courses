package p1;

public abstract class ToppingDecorator implements IceCream {
    private IceCream tempIceCream;

    public ToppingDecorator(IceCream decoratedIceCream) {
        tempIceCream = decoratedIceCream;
    }

    public String getDescription() {
        return tempIceCream.getDescription();
    }

    public double getPrice() {
        return tempIceCream.getPrice();
    }
}
