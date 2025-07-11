package p1;

public class Main {
    static int coreCount = 8;

    public static void main(String[] args) {
        HelloWorld[] threads = new HelloWorld[coreCount];

        for (int i = 0; i < coreCount; i++) {
            threads[i] = new HelloWorld(i);
            threads[i].start();
        }

        for (int i = 0; i < coreCount; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
