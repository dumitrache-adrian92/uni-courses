package lab3.p1;

public class Fractie {
    int numarator, numitor;

    public Fractie(int alaDeSus, int alaDeJos) {
        numarator = alaDeSus;
        numitor = alaDeJos;
    }

    public Fractie() {
        this(0, 1);
    }

    public Fractie add(Fractie x) {
        Fractie sum = new Fractie(numarator, numitor);
        sum.numarator = sum.numarator * x.numitor + x.numarator * sum.numitor;
        sum.numitor = sum.numitor * x.numitor;
        return sum;
    }

    public String toString() {
        String s = numarator + " / " + numitor;
        System.out.println(s);
        return s;
    }

    public boolean equals(Object a) {
        if (!(a instanceof Fractie))
            return false;
        Fractie x = (Fractie)a;
        return numarator == x.numarator && numitor == x.numitor;
    }
    public static void main(String[] args) {
        Fractie x = new Fractie(5, 3);
        Fractie y = new Fractie(6, 4);

        x.add(y).toString();
        System.out.println(x.equals(y));
        System.out.println(x.equals(x));
    }
}