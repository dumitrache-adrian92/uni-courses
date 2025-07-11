package task1;

import java.util.ArrayList;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.atomic.AtomicInteger;

public class GetAllPaths implements Runnable {
    int[][] graph;
    ArrayList<Integer> partialPath;
    int destination;
    ExecutorService executorService;
    AtomicInteger count;

    public GetAllPaths(ArrayList<Integer> partialPath, int destination, int[][] graph, ExecutorService executorService, AtomicInteger count) {
        this.executorService = executorService;
        this.graph = graph;
        this.partialPath = partialPath;
        this.destination = destination;
        this.count = count;
    }

    @Override
    public void run() {
        if (partialPath.get(partialPath.size() - 1) == destination) {
            System.out.println(partialPath);
            if (count.decrementAndGet() == 0)
                executorService.shutdown();

            return;
        }

        // se verifica nodurile pentru a evita ciclarea in graf
        int lastNodeInPath = partialPath.get(partialPath.size() - 1);
        for (int[] ints : graph) {
            if (ints[0] == lastNodeInPath) {
                if (partialPath.contains(ints[1]))
                    continue;
                ArrayList<Integer> newPartialPath = new ArrayList<>(partialPath);
                newPartialPath.add(ints[1]);
                count.incrementAndGet();
                executorService.submit(new GetAllPaths(newPartialPath, destination, graph, executorService, count));
            }
        }

        count.decrementAndGet();
    }
}
