package p4;

import java.io.*;

public class wordCount {
    public static void main(String[] args) throws FileNotFoundException {
        try {
            FileReader in = new FileReader(new File("src/p4/test02.in"));
            StreamTokenizer st = new StreamTokenizer(in);

            int count = 0;

            int currentToken = st.nextToken();
            while (currentToken != StreamTokenizer.TT_EOF) {
                count++;
                currentToken = st.nextToken();
            }

            System.out.println(count);
        }
        catch (FileNotFoundException fileNotFoundException) {
            System.out.println("File doesn't exist.");
            return;
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
