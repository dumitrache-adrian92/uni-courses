package p1;

public class Dreptunghi extends Paralelogram{
    public Dreptunghi() {
        super();
    }

    public Dreptunghi(int l1, int l2) {
        super(l1, l2, 90.0, 90.0);
    }

    public double arie() {
        return latura1 * latura2;
    }
}
