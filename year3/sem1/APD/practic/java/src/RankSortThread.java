import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;

public class RankSortThread implements Runnable {
    private int[] array;
    private int start;
    private int end;
    private int id;
    private CyclicBarrier barrier;

    public RankSortThread(int[] array, int id, CyclicBarrier barrier) {
        this.array = array;
        this.id = id;
        this.start = id * array.length / RankSort.P;
        this.end = (id + 1) * array.length / RankSort.P;
        this.barrier = barrier;
    }

    @Override
    public void run() {
        for (int i = start; i < end; i++) {
            int rank = 0;
            for (int j = 0; j < array.length; j++) {
                if (array[j] < array[i]) {
                    rank++;
                }
            }
            RankSort.result[rank] = array[i];
        }
        try {
            barrier.await();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        } catch (BrokenBarrierException e) {
            throw new RuntimeException(e);
        }

        if (id == 0) {
            for (int i = 0; i < RankSort.result.length; i++) {
                System.out.print(RankSort.result[i] + " ");
            }
        }
    }
}
