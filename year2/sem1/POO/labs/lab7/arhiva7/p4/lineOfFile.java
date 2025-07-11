package p4;

import java.io.*;
import java.util.*;

public class lineOfFile {
    public static void main(String[] args) throws IOException {
        TreeMap<String, LinkedList> wordLines = new TreeMap<String, LinkedList>();
        File file=new File("/home/adrian/test01.txt");    //creates a new file instance
        FileReader fr=new FileReader(file);   //reads the file
        BufferedReader br=new BufferedReader(fr);
        String line;
        String[] words;
        int i = 1;

        while((line = br.readLine()) != null) {
            words = line.split(" ");
            for (String word:
                 words) {
                if (!wordLines.containsKey(word))
                    wordLines.put(word, new LinkedList());
                wordLines.get(word).add(i);
            }
            i++;
        }

        Set keys = wordLines.entrySet();
        Iterator it = keys.iterator();

        while(it.hasNext()) {
            System.out.println(it.next());
        }

    }
}
