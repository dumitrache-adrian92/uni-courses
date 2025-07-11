package task3;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.atomic.AtomicInteger;

public class Queens implements Runnable {
    int[] graph;
    int step;
    ExecutorService executor;
    AtomicInteger counter;

    public Queens(int[] graph, int step, ExecutorService executor, AtomicInteger counter) {
        this.graph = graph;
        this.step = step;
        this.executor = executor;
        this.counter = counter;
    }

    @Override
    public void run() {
        if (Main.N == step) {
            Main.printQueens(graph);
            if (counter.decrementAndGet() == 0)
                executor.shutdown();
            return;
        }

        for (int i = 0; i < Main.N; ++i) {
            int[] newGraph = graph.clone();
            newGraph[step] = i;

            if (Main.check(newGraph, step)) {
                counter.incrementAndGet();
                executor.submit(new Queens(newGraph, step + 1, executor, counter));
            }
        }

        if (counter.decrementAndGet() == 0)
            executor.shutdown();
    }
}
