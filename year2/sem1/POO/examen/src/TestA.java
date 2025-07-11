public class TestA {
    static void test() {
        try {
            String x = null;
            System.out.println(x.toString());
        } finally {
            System.out.println("FINALLY ");
        }
    }

    public static void main(String[] args) {
        try {
            test();
        } catch (Exception exc) {
            System.out.println("exc");
        }
    }
}
