package task6;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.RecursiveTask;

public class QueensForkJoin extends RecursiveTask<Void> {
    int[] graph;
    int step;

    public QueensForkJoin(int[] graph, int step) {
        this.graph = graph;
        this.step = step;
    }

    @Override
    protected Void compute() {
        if (Main.N == step) {
            Main.printQueens(graph);
            return null;
        }
        List<QueensForkJoin> tasks = new ArrayList<>();
        for (int i = 0; i < Main.N; ++i) {
            int[] newGraph = graph.clone();
            newGraph[step] = i;

            if (Main.check(newGraph, step)) {
                QueensForkJoin queensForkJoin = new QueensForkJoin(newGraph, step + 1);
                tasks.add(queensForkJoin);
                queensForkJoin.fork();
            }
        }

        for (QueensForkJoin task : tasks) {
            task.join();
        }

        return null;
    }
}
