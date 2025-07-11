package p4;

import java.io.*;
import java.util.Vector;

public class Filtru implements FilenameFilter {
    Vector extensions = new Vector();
    Vector cuv = new Vector();

    public Filtru(File f1, File f2) throws IOException {
        FileReader fr1 = new FileReader(f1);   //reads the file
        BufferedReader br1 = new BufferedReader(fr1);

        String line;
        String[] words;
        while((line = br1.readLine()) != null) {
            words = line.split("\n ");
            for (String word:words) {
                cuv.add(word);
            }
        }

        FileReader fr2 = new FileReader(f2);   //reads the file
        BufferedReader br2 = new BufferedReader(fr2);

        while((line = br1.readLine()) != null) {
            words = line.split("\n ");
            for (String word:words) {
                extensions.add(word);
            }
        }

    }

    public boolean accept(File dir, String name) {
        int i = 0;
        for(i = 0; i < cuv.size(); i++) {
            if (name.contains((String)cuv.get(i)))
                return true;
        }

        for(i = 0; i < extensions.size(); i++) {
            if (name.endsWith((String)extensions.get(i)))
                return true;
        }

        return false;
    }

    public static void main(String[] args) throws IOException {
        File file1 = new File("/home/adrian/Dropbox/uni/POO/labs/lab6/p4/words.in");
        File file2 = new File("/home/adrian/Dropbox/uni/POO/labs/lab6/p4/extension.in");
        File file3 = new File("/home/adrian/Dropbox/uni/POO/labs/lab6/p4/director");
        Filtru f = new Filtru(file1, file2);
        File[] files = file3.listFiles(f);
        for (File file : files) {
            if (file.isDirectory()) {
                System.out.print("directory:");
            } else {
                System.out.print("     file:");
            }
            System.out.println(file.getCanonicalPath());
        }
    }
}
