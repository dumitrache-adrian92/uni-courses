package p1;

public class Patrat extends Dreptunghi{
    public Patrat() {
        super();
    }

    public Patrat(int l1) {
        super(l1, l1);
    }

    public double arie() {
        return latura1 * latura2;
    }
}
