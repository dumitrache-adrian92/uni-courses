package task5;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.RecursiveTask;

public class ColorForkJoin extends RecursiveTask<Void> {
    int[] colors;
    int step;

    public ColorForkJoin(int[] colors, int step) {
        this.colors = colors;
        this.step = step;
    }

    @Override
    protected Void compute() {
        if (step == Main.N) {
            Main.printColors(colors);
            return null;
        }

        // for the node at position step try all possible colors
        List<ColorForkJoin> tasks = new ArrayList<>();
        for (int i = 0; i < Main.COLORS; i++) {
            int[] newColors = colors.clone();
            newColors[step] = i;
            if (Main.verifyColors(newColors, step)) {
                ColorForkJoin colorForkJoin = new ColorForkJoin(newColors, step + 1);
                tasks.add(colorForkJoin);
                colorForkJoin.fork();
            }
        }

        for (ColorForkJoin task : tasks) {
            task.join();
        }

        return null;
    }
}
