package lab3.p5;

public class Test {
    public static void main(String[] args) {
        Punct a = new Punct();
        Punct b = new Punct();
        a.setX(1);
        a.setY(2);

        b.setX(-1);
        b.setY(3);

        System.out.println(a.distance(b));
    }
}
