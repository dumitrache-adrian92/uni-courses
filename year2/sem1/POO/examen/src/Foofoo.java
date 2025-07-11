class Lol {
    static Bilant s = new Bilant();

    public static void main(String[] args) {
        new Lol().met(s);
        System.out.println(s);
    }

    void met(Bilant s) {
        s.pozitive = 5000;
        s.negative = 6000;
    }
}