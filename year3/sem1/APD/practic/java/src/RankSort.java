import java.util.concurrent.CyclicBarrier;

public class RankSort {
    public static int result[];
    public static int P;
    public static int N;

    public static void main(String[] args) {
        N = Integer.parseInt(args[0]);
        P = Integer.parseInt(args[1]);

        Thread[] threads = new Thread[P];
        CyclicBarrier barrier = new CyclicBarrier(P);
        int[] array = new int[N];
        result = new int[N];

        for (int i = 0; i < N; i++) {
            array[i] = N - i + 5;
        }

        for (int i = 0; i < P; i++) {
            threads[i] = new Thread(new RankSortThread(array, i, barrier));
        }

        for (int i = 0; i < P; i++) {
            threads[i].start();
        }

        for (int i = 0; i < P; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }
    }
}