public class Errors {
    public static void main(String[] args) {
        try {
            throw new Error();
        } catch (Error e) {
            try {
                throw new RuntimeException();
            } catch (Throwable t) {

            }
        }
        System.out.println("penis");
    }
}
