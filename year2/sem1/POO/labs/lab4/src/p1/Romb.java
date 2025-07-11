package p1;

public class Romb extends Paralelogram{
    int diag1, diag2;

    public Romb() {
        super();
    }

    public Romb(int l1) {
        super(l1, l1);
    }

    public Romb(double u1, double u2) {
        super(u1, u2);
    }

    public Romb(int l1, double u1, double u2) {
        super(l1, l1, u1, u2);
    }

    public Romb(int l1, double u1, double u2, int diag1, int diag2) {
        super(l1, l1, u1, u2);
        this.diag1 = diag1;
        this.diag2 = diag2;
    }

    public double arie() {
        return (diag1 * diag2) / 2;
    }
}
