package p1;

import com.sun.source.util.Trees;

import java.io.*;
import java.util.Collections;
import java.util.Comparator;
import java.util.TreeSet;

public class TreeSetTest {
    public TreeSet printWords(String filename) throws IOException {
        TreeSet<String> result = new TreeSet();
        File file=new File(filename);    //creates a new file instance
        FileReader fr=new FileReader(file);   //reads the file
        BufferedReader br=new BufferedReader(fr);
        String line;
        String[] words;

        while((line = br.readLine()) != null) {
            words = line.split(" ");
            Collections.addAll(result, words);
        }

        for (Object i:
             result) {
            System.out.println((String) i);
        }

        return result;
    }

    public TreeSet printWordsComparator(TreeSet ts) {
        Comparator<String> c = Comparator.comparing(String::toString);
        TreeSet result = new TreeSet(c.reversed());
        result.addAll(ts);

        System.out.println();
        for (Object i:
                result) {
            System.out.println((String) i);
        }
        return result;
    }

    public static void main(String[] args) throws IOException {
        TreeSetTest tst = new TreeSetTest();
        tst.printWordsComparator(tst.printWords("/home/adrian/test01.txt"));
    }
}
