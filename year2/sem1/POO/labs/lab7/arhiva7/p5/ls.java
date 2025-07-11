package p5;

import java.io.File;
import java.nio.file.Files;
import java.util.*;

public class ls {
    HashMap<String, Integer> files;
    File directory;

    public ls(String directory) {
        files = new HashMap<String, Integer>();
        this.directory = new File(directory);
        File[] allFiles = this.directory.listFiles();
        for (File f: allFiles) {
            int x = (int) f.length();
            files.put(f.getName(), (Integer)x);
        }
    }

    public void run(Comparator c) {
        List<String> keys = new ArrayList<>(files.keySet());
        Collections.sort(keys, c);
        for(String i:keys) {
            System.out.println(i + " = " + files.get(i));
        }
    }

    public static void main(String[] args) {
        ls out = new ls("/home/adrian");

        out.run(null);
    }
}
