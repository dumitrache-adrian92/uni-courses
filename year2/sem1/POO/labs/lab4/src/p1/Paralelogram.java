package p1;

public class Paralelogram extends Patrulater {
    public Paralelogram() {
        super(0, 0, 0, 0);
    }
    public Paralelogram(int l1, int l2) {
        super(l1, l2, l1, l2);
    }

    public Paralelogram(int l1, int l2, double u1, double u2) {
        super(l1, l2, l1, l2, u1, u2, u1, u2);
    }

    public Paralelogram(double u1, double u2) {
        this(0, 0, u1, u2);
    }

    public double arie() {
        return latura1 * latura2 * Math.sin(unghi1 * Math.PI / 180);
    }
}
