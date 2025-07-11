package p4;

public class Pensionar {
    private int aniVechime;
    private float salariu;
    private Strategy strategy;

    public Pensionar(int aniVechime, float salariu) {
        this.aniVechime = aniVechime;
        this.salariu = salariu;
        if (20 <= aniVechime && aniVechime < 30)
            strategy = new TwentyStrategy();
        else if (30 <= aniVechime && aniVechime < 40)
            strategy = new ThirtyStrategy();
        else if (40 <= aniVechime)
            strategy = new FortyStrategy();
        else
            strategy = null;
    }

    public float getPensie() {
        if (strategy == null)
            return 0;
        else
            return strategy.calcul(aniVechime, salariu);
    }

    public static void main(String[] args) {
        Pensionar p1 = new Pensionar(25, 100);
        Pensionar p2 = new Pensionar(33, 100);
        Pensionar p3 = new Pensionar(41, 100);
        Pensionar vaiSamar = new Pensionar(0, 100);

        System.out.println(p1.getPensie());
        System.out.println(p2.getPensie());
        System.out.println(p3.getPensie());
        System.out.println(vaiSamar.getPensie());
    }
}
