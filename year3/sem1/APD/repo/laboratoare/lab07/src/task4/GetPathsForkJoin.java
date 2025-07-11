package task4;
import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveTask;
import java.util.concurrent.atomic.AtomicInteger;

public class GetPathsForkJoin extends RecursiveTask<Void> {
    ArrayList<Integer> partialPath;
    int destination;

    public GetPathsForkJoin(ArrayList<Integer> partialPath, int destination) {
        this.partialPath = partialPath;
        this.destination = destination;
    }

    @Override
    protected Void compute() {
        if (partialPath.get(partialPath.size() - 1) == destination) {
            System.out.println(partialPath);
            return null;
        }

        // se verifica nodurile pentru a evita ciclarea in graf
        int lastNodeInPath = partialPath.get(partialPath.size() - 1);
        List<GetPathsForkJoin> tasks = new ArrayList<>();
        for (int[] ints : Main.graph) {
            if (ints[0] == lastNodeInPath) {
                if (partialPath.contains(ints[1]))
                    continue;
                ArrayList<Integer> newPartialPath = new ArrayList<>(partialPath);
                newPartialPath.add(ints[1]);
                GetPathsForkJoin getParkForkJoin = new GetPathsForkJoin(newPartialPath, destination);
                tasks.add(getParkForkJoin);
                getParkForkJoin.fork();
            }
        }

        for (GetPathsForkJoin task : tasks) {
            task.join();
        }

        return null;
    }
}
