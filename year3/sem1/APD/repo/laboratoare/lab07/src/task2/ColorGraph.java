package task2;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.atomic.AtomicInteger;

public class ColorGraph implements Runnable {
    int[] colors;
    AtomicInteger inQueue;
    ExecutorService executorService;
    int step;

    public ColorGraph(int[] colors, AtomicInteger inQueue, ExecutorService executorService, int step) {
        this.colors = colors;
        this.inQueue = inQueue;
        this.executorService = executorService;
        this.step = step;
    }

    @Override
    public void run() {
        if (step == Main.N) {
            Main.printColors(colors);

            if (inQueue.decrementAndGet() == 0)
                executorService.shutdown();

            return;
        }

        // for the node at position step try all possible colors
        for (int i = 0; i < Main.COLORS; i++) {
            int[] newColors = colors.clone();
            newColors[step] = i;
            if (Main.verifyColors(newColors, step)) {
                inQueue.incrementAndGet();
                executorService.submit(new ColorGraph(newColors, inQueue, executorService, step + 1));
            }
        }

        if (inQueue.decrementAndGet() == 0)
            executorService.shutdown();
    }
}
