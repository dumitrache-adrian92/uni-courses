package p2;

import java.io.*;

public class OddLines {
    public static void main(String[] args) throws IOException {
        FileReader fr = new FileReader("src/p2/test01.in");

        LineNumberReader lnr = new LineNumberReader(fr);

        try {
            int lineNumber = lnr.getLineNumber() + 1;
            String currentLine = lnr.readLine();
            while (currentLine != null) {
                // print numbered line
                System.out.println(lineNumber + " " + currentLine);

                // skip even line
                lnr.readLine();

                // get next odd line
                lineNumber = lnr.getLineNumber() + 1;
                currentLine = lnr.readLine();
            }
        }
        catch (IOException e) {
            fr.close();
            lnr.close();
            return;
        }

        fr.close();
        lnr.close();
    }
}
